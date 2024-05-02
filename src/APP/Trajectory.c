#include <stdio.h>
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/HAL/LCD.h"



//draw_path Receives 2 points from those stored in pui32Data(that stores points in EEPROM) as two dim array

/*pui32Data is an array that holds four words(2 points) that later will be sent to be stored in EEPROM(in EEPROMProgram(pui32Data, p, sizeof(pui32Data)); )*/				
/*In pui32Data , it holds four words at a time (0-->16) where each two words represent a point(latitude,longitude respectivelly) */
/* 0-->4 lat of P1 , 4-->8 long of P1*/
/*8-->12 lat of P1(in the following loop), 12-->16 long of P1 (in the following loop)*/

/*in two dim array x: */
/*columns hold different points (each loop of the above main for loop stores two points in test array) and each row holds lat/long of the point as char*/
/*example: first loop, first row holds lat of first point read from EEPROM as char, second row holds long of first point read from EEPROM as char*/
/*third row holds lat of second point read from EEPROM as char, fourth row holds long of second point read from EEPROM as char*/
void draw_path(char x[4][6]) {
	char m,n,b;
	for(n=0;n<4;n++){
	    b=0;
	    if(n==1){
	        UART0_Transmitter(','); 												//sends a "," after receiving lat of first point to separate lat and long
	        delayMs(250);}
	    else if(n==2){
	        UART0_Transmitter('@');												 //sends a "@" to indicate a new line after receiving lat&long of first point to separate first point from the following point
	        delayMs(250);
	    }
	    if(n==3){
	          UART0_Transmitter(',');											//sends a "," after receiving lat of second point to separate lat and long
	          delayMs(250);}

		for(m=0;m<6;m++){
			/*previously done in main.c: if latitude is received as 51.3863932 for example, then we multiply by 10^4 and take integer part only (513863) which later is converted back to (51,3863) in draw_path func in Trajectory.c */ 
		    if(b==2)UART0_Transmitter('.'); //converts for example 513863 back to 51.3863

		    delayMs(500);
			if(x[n][m]!=0xf) {
				UART0_Transmitter(x[n][m]);										//IF data read from EEPROM is not null then send data
				delayMs(250);
			}
			b++;
		}}
	            UART0_Transmitter('@');								//sends a "@" to indicate a new line
	            delayMs(250);

}
