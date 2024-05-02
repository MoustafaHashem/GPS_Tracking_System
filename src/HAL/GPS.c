# include "../../Headers/HAL/GPS.h "
# include "../../Services/bit_utilies.h "
#include "../../Headers/MCAL/UART.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
const float   pi	=	3.14285 ,earth_redus	=6371000;
//char data[80]={'0','9','2','9','1','5','.','0','0',',','A',',','3','0','0','3','.','9','1','4','2','0',',','N',',','0','3','1','1','6','.','7','9','5','6','5',',','E',',','2','.','4','5','9',',',',','2','7','0','4','2','4',',',',',',','A','*'};
char static data[80];
char* x =&data[0];
char filterData[12][20];
char * token;
char logName[]="$GPRMC,";
char z;
char test;
char flag=1;
//char i;
	float draft,draft1,draft2;
//float P1Long=31.335822222222222,P1Lat=30.15138888888889,speed=0,	 P2Long=31.334722222222222, P2Lat=30.151388999999998;
float P1Long,P1Lat,speed,P2Long, P2Lat;

void readData(){
	char b=0;
	z=0;
	//i=0;
		do{
		
		while(UART7_Receiver()!= logName[z]){												/*wait for the segment from the GPS that contains Time, date, position, course and speed data which has all the data we need*/
		}
				//UART0_Transmitter(logName[z]);
		z++;
		}
		 /*GPS data starts like this "$GPRMS," then availablity, position and speed data follows so here we wait till index equals 7 (first element after "," in "$GPRMS,") then start storing data from GPS to work on later*/
		while(z!=7);																							
		strcpy(data,"");																						//initialize/clear data to start receiving data needed from GPS 
		do{
			
		  test=UART7_Receiver();                                   /*test is a temporary register that will hold the data received from GPS then transfer it to the actual array that holds the data "data"*/
			data[b++]=test;
	//UART0_printstring(data); //testing
		}while(test != '*');																			/*on reaching "*" (end of needed data in the received segment), stop receiving data*/
}
void doFilter(){
	char x=0;
	//UART0_printstring(data); //testing
		token=strtok(data,",");																		/*separate the data separated by "," and store as individual segments in token*/
	do{
		int o=x++;
	strcpy(filterData[o],token);                                /*store the separated individual data segments in filterData array , now we have each on its own stored in the array (availability,longitude,latitude,speed)*/
	//UART0_printstring(filterData[o]); //testing
						

	token=strtok(NULL,",");																			/*To keep separating the data whenever a "," is found till reaching the end of the string*/
		
	}while(token!=NULL);
	if(!strcmp(filterData[1],"A")){															/*If filterData[1] is "A" (which means data is available from GPS) then carry on with the code*/
			if(!strcmp(filterData[3],"N")){													
			draft =atof(filterData[2]);															/*If latitude is followed by "N" then leave it positiveinP1Lat)*/
				/*The following are calculations to receive/make longitude and latitude positions as that used by google maps to be able to send them and draw the trajectory correctly later on*/ 
				draft1=draft/100;
				draft2=(int)draft1;
				draft1=draft1-draft2;
				draft1=(draft1*100)/60;
				P1Lat=draft2+draft1;																	/*P1 latitude correctly after calculations are done*/
				//clear variables for the next loop
				draft=0;
				draft1=0;
				draft2=0;
			}
				else{
			  draft =-atof(filterData[2]);														/*If latitude is followed by "S" then make it negative(inP1Lat) */
				/*The following are calculations to receive/make longitude and latitude positions as that used by google maps to be able to send them and draw the trajectory correctly later on*/ 
				draft1=draft/100;
				draft2=(int)draft1;
				draft1=draft1-draft2;
				draft1=(draft1*100)/60;
				P1Lat=-(draft2+draft1);																/*P1 latitude correctly after calculations are done*/			
					//clear variables for the next loop
				draft=0;
				draft1=0;
				draft2=0;
			}
			if(!strcmp(filterData[5],"E")){
				draft =atof(filterData[4]);														/*If longitude is followed by "E" then make it positive(inP1Long) */
				/*The following are calculations to receive/make longitude and latitude positions as that used by google maps to be able to send them and draw the trajectory correctly later on*/ 
				draft1=draft/100;
				draft2=(int)draft1;
				draft1=draft1-draft2;
				draft1=(draft1*100)/60;
				P1Long=draft2+draft1;																	/*P1 longitude correctly after calculations are done*/	
				//clear variables for the next loop
				draft=0;
				draft1=0;
				draft2=0;
			}
			else{
			draft =atof(filterData[4]);														/*If longitude is followed by "W" then make it negative(inP1Long) */
				/*The following are calculations to receive/make longitude and latitude positions as that used by google maps to be able to send them and draw the trajectory correctly later on*/ 
				draft1=draft/100;
				draft2=(int)draft1;
				draft1=draft1-draft2;
				draft1=(draft1*100)/60;
				P1Long=-(draft2+draft1);														/*P1 longitude correctly after calculations are done*/
				//clear variables for the next loop
				draft=0;
				draft1=0;
				draft2=0;
			}
		speed=atof(filterData[6]);
			/*The code of the followig if makes p1 and p2 equal because at first starting the program (No motion yet) the start point is the same as destination point*/
			/*This code is executed only once when there is no motion yet, once motion is detected p1 becomes the new reaches/latter point and p2 old/last reached point (that's why flag is set to zero after first loop)*/
		if(flag){
		P2Long=P1Long;
		P2Lat=P1Lat;
			flag=0;
		}	
	}
}
//function to convert an angle from rad to degree
float toDegree(float angle){
			int degree= (int)angle/100;
			float minutes =angle - (float)degree*100;
			return (degree+(minutes/60));
}
//function to convert an angle from degree to rad
float toRad(float angle){
return (angle*(3.14/180));
}
//Function to calculate the distance between P1(newly reached point) and P2(last reached point)
float calculatDesenation(float long1,float lat1,float long2,float lat2){
			float long1InRad=toRad(long1);
			float lat1InRad=toRad(lat1);
			float long2InRad=toRad(long2);
			float lat2InRad=toRad(lat2);
			float deltaLat=toRad(lat2-lat1);
			float delatLong=toRad(long2-long1);
			float a=	pow(sin((deltaLat)/2),2)+cos(lat1InRad)*cos(lat2InRad)*pow(sin((delatLong)/2),2);
			float c= 2*atan2(sqrt(a),sqrt(1-a));
			float z= 6371000*c;
			return z;
}
//getters and setters
float getP1Long(){return P1Long;}												//return P1(newly reached point) longitude
float getP1Lat(){return P1Lat;}													//return P1(newly reached point) latitude
float getspeed(){return speed;}													//return speed	
float getP2Long(){return P2Long;}												//return P2(last reached point) longitude
float getP2Lat(){return P2Lat;}													//return P2(last reached point) latitude
void setP2Long(float x){ P2Long=x;} 										//set P2(last reached point) longitude                    
void setP2Lat(float x){ P2Lat=x;}												//set P2(last reached point) latitude

































