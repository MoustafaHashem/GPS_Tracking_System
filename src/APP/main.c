#include "../../Headers/HAL/GPS.h"
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/HAL/LCD.h"
#include "../../Headers/Trajectory.h"
#include <stdint.h>
#include <stdbool.h>
#include"inc/hw_types.h"
#include"inc/hw_memmap.h"
#include"driverlib/sysctl.h"
#include"driverlib/pin_map.h"
#include"driverlib/debug.h"
#include"driverlib/gpio.h"
#include"driverlib/flash.h"
#include"driverlib/eeprom.h"
#include <math.h>
#include <stdio.h>

char* welcome=	  "welcome ";
char* SW1= 				"SW1 to start";
char* SW2= 	"SW2 to print";
char* str = 			"Distance= ";    							//Write any string you want to display on LCD
char* str2 =			"AVGSpeed= ";  							  //Write any string you want to display on LCD
char* close =			"Or turn off tiva";  					//Write any string you want to display on LCD
char* draw1 =			"Trajectory";  							  //Write any string you want to display on LCD
char* draw2 =			"drawing";  							    //Write any string you want to display on LCD

char myStg[5];
int i=1;
int l,m,n,p=0,k=1,cc;
float totalS=0,totalD=0,totalD2=1;  		// ###totD must store in eeprom too
uint32_t pui32Data[4];
uint32_t pui32Read[4];
char* print;
char test[11];
char f[4][6];
int main() {
  //Initialization:                                                          
  SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
  EEPROMInit();
	UART0_Initialaize ();
  UART7_Initialaize ();
	GPIO_PORTF_initialization();
	LCD4bits_Init();									
	//**********************************************************************
	//LCD display and formatting
	LCD4bits_Cmd(0x01);								//Clear the display
	displayLine1(welcome);
	LCD4bits_Cmd(0x01);								//Clear the display
	displayLine1(SW1);
	displayLine2(SW2);
	//**********************************************************************
	while(1){
		    if(get_Switch_value(GPIO_SW1)==0){
			LCD4bits_Cmd(0x01);						 //Clear the display
			displayLine1(str);
			displayLine2(str2);
			EEPROMMassErase();						// ###here must clear all points in  eeprom
			while(1){           
			  delayMs(1000);              // ##delay bet points
				readData(); 								//read data from GPS (as explained in GPS.c)
			  doFilter(); 								//filter read data from GPS (as explained in GPS.c)
				totalD=totalD+calculatDesenation(getP2Long(),getP2Lat(),getP1Long(),getP1Lat()); /*add the new distance between P1(the newly reached point) and P2(last reached point/ point we last stopped at) to the total distance*/
				
				//Make the last point we reached as P2 for the next loop
				setP2Long(getP1Long());			
				setP2Lat(getP1Lat());			
				
				//Formatting for LCD
				sprintf(myStg, "%.2f", totalD);
				displayWithCursor(myStg,0x8A);			
				
				totalS=(totalS+getspeed())/++i; //add new speed to total speed and divide by their number to get average speed
				
				//Formatting for LCD
				sprintf(myStg, "%.2f", totalS);	
				displayWithCursor(myStg,0xCA);
				
				//explained in GPIO.c
				set_led(totalD);


//The following code is used to store data in EEPROM
/*pui32Data is an array that holds four words(2 points) that later will be sent to be stored in EEPROM(in EEPROMProgram(pui32Data, p, sizeof(pui32Data)); )*/				
/*In pui32Data , it holds four words at a time (0-->16) where each two words represent a point(latitude,longitude respectivelly) */
/* 0-->4 lat of P1 , 4-->8 long of P1*/
/*8-->12 lat of P1(in the following loop), 12-->16 long of P1 (in the following loop)*/
				if((p!=64)&&(totalD>totalD2)){
				    totalD2=totalD+13.5;                                                        // store point each 13.5 m
					//store first point (lat,long) in the first two words in pui32Data
				if(k%2!=0){
				    pui32Data[0]=getP1Lat()*(1e4);   /*if latitude is received as 51.3863932 for example, then we multiply by 10^4 and take integer part only (513863) which later is converted back to (51,3863) in draw_path func in Trajectory.c */ 
				    pui32Data[1]=getP1Long()*(1e4);  //same as latitude
				}
				//store following point (lat,long) in the last two words in pui32Data
				else{
				    pui32Data[2]=getP1Lat()*(1e4);
				    pui32Data[3]=getP1Long()*(1e4);
				
		            EEPROMProgram(pui32Data, p, sizeof(pui32Data)); /*Send the two points to EEPROM to be stored, after finishing the loop(when we break from it when sw1 is pressed) EEPROM will hold 8 points to later draw the trajectory*/
		            p=p+16;																					//Move tto the next segment in EEPROM		
				}
			  k=k+1;
				    }
/*If SW1 is pressed and total covered distance is found to be >100 either choose SW2 to print trajectory or close the program(but trajectory won't be lost because it will be stored in EEPROM)*/
				if((get_Switch_value(GPIO_SW1)==0)&&(totalD>100)){
					LCD4bits_Cmd(0x01);						 										//Clear the display
					displayLine1(SW2);
					displayLine2(close);
					break;
				}
			}
		}
				
		
		if((get_Switch_value(GPIO_SW2)==0)){
			LCD4bits_Cmd(0x01);																		//Clear the display
			displayLine1(draw1);
			displayLine2(draw2);			
			LCD4bits_Cmd(0x01);                             			//Clear the display
			 displayLine1("loading");															//waiting for trajectory to be drawn
			for(n=0;n<64;n+=16){
			EEPROMRead(pui32Read, n, sizeof(pui32Read));					//Reading the 2 points from those stored in EEPROM each loop to be sent to Intellij to draw trajectory
			    SysCtlDelay(2000000);
			    int sasa,soso;
				/*The following nested for loops store the points read from EEPROM as characters in a two dimensional array "f"*/
				/* where columns hold different points (each loop of the above main for loop stores two points in test array) and each row holds lat/long of the point as char*/
				/*example: first loop, first row holds lat of first point read from EEPROM as char, second row holds long of first point read from EEPROM as char*/
			  /*third row holds lat of second point read from EEPROM as char, fourth row holds long of second point read from EEPROM as char*/
						for(sasa=0;sasa<4;sasa++){
                sprintf(test, "%i", pui32Read[sasa]); /*test is a temp array that reads elements(lat/long) stored in pui32Data*/
                for(soso=0;soso<6;soso++){
			    f[sasa][soso]=test[soso];
                }
			    }
			   draw_path(f);																			//sends each two points stored in f array in each loop to Intellij for trajectory to be drawn after finishing main for loop(explained more in Trajectory.c)
			    }
			UART0_Transmitter('^');																//When this character is received by Intellij, it stops receiving points and satrts drawing trajectory
			LCD4bits_Cmd(0x01);                            				//Clear the display
			displayLine1("done");
		  displayLine2("Thank you");
      LCD4bits_Cmd(0x01);                             //Clear the display
      displayLine1(SW1);
      displayLine2(close);
			}
	}
 }
