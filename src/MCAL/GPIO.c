#include "../../Headers/MCAL/GPIO.h"
#include "../../Services/TM4C123.h "
#include "../../Services/bit_utilies.h"
void GPIO_PORTF_initialization(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,5); 									//Activate clock for portF
	while(GET_BIT(SYSCTL_PRGPIO_R,5) == 0); 				//Wait for Stabilization
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; 							//Unlock GPIO portF
	GPIO_PORTF_CR_R |= 0x1F; 												//Allow changes to PF4-0
	GPIO_PORTF_AMSEL_R &= ~(0x1F); 									//Disable analog on PF
	GPIO_PORTF_AFSEL_R &= ~(0x1F); 									//Disable alt func on PF4-0
	GPIO_PORTF_PCTL_R &= ~(0x000FFFFF); 						//PCTL GPIO on PF4-0
	GPIO_PORTF_DEN_R |= 0x1F; 											//Enable digital I/O on PF4-0
	GPIO_PORTF_DIR_R |= 0x0E; 		               		//PF3-1 LEDs out
	GPIO_PORTF_DIR_R &=~0x11; 											//PF4,PF0 swicthes in 
	GPIO_PORTF_DATA_R &= ~(0x1F); 									//Clear Data bits of PF4-0
	GPIO_PORTF_PUR_R |= 0x11; 											//Enable Pull-up on PF4 ,PF0 (switches),Enable negative logic for the switches
}
void GPIO_PORTB_initialization(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,1); 									//Activate clock for portB
	while(GET_BIT(SYSCTL_PRGPIO_R,1) == 0); 				//Wait for Stabilization
	GPIO_PORTB_CR_R |= 0xFF; 												//Allow changes to PB7-PB0
	GPIO_PORTB_AMSEL_R &= ~(0xFF); 									//Disable analog on PB7-PB0
	GPIO_PORTB_AFSEL_R &= ~(0xFF); 									//Disable alt func on PB7-PB0
	GPIO_PORTB_PCTL_R &= ~(0xFFFFFFFF); 						//PCTL GPIO on PB7-PB0
	GPIO_PORTB_DEN_R |= 0xFF; 											//Enable digital I/O on PB7-PB0
	GPIO_PORTB_DATA_R &= ~(0xFF); 									//Clear Data bits of PB7-PB0
	GPIO_PORTB_DIR_R |= 0xFF;												//PB7-PB0 out
}
void GPIO_PORTE_initialization(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,4); 									//Activate clock for portE
	while(GET_BIT(SYSCTL_PRGPIO_R,4) == 0); 				//Wait for Stabilization
	GPIO_PORTE_CR_R |= 0x33; 												//Allow changes to PE5,PE4,PE1,PE0
	GPIO_PORTE_AMSEL_R &= ~(0x33); 									//Disable analog on PE5,PE4,PE1,PE0
	GPIO_PORTE_AFSEL_R |= (0x30); 									//Enable alt func on PE5,PE4
	GPIO_PORTE_PCTL_R |= (0x110000); 						    //PCTL UART on PE5,PE4
	GPIO_PORTE_DEN_R |= 0x33; 											//Enable digital I/O on PE5,PE4,PE1,PE0
	GPIO_PORTE_DATA_R &= ~(0x33); 									//Clear Data bits of PE5,PE4,PE1,PE0
	//PE4(GPS UART Rx-->in) , PE5(GPS UART Tx-->out) , PE0(GPS VDD-->in) , PE1(GPS GND-->in)
	GPIO_PORTE_DIR_R &=~ (0x13);										//PE0(VDD),PE1(GND),PE4(Receiver)-->in
	GPIO_PORTE_DIR_R |= 0x20;												//PE5(transmitter)-->out
}
void switch_ledState(unsigned char ledColor, unsigned char ledState){

	switch(ledState){
		case GPIO_LED_ON:  SET_BIT(GPIO_PORTF_DATA_R,ledColor); break; 						//turn ON Led (set LED pin in data register according to ledColor)
		case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,ledColor); break; 						//turn OFF Led(clear LED pin in data register according to ledColor)
		default: break;
}
}


//Function to set a certain LED ON/OFF
void GPIO_set_LEDs_value(unsigned char ledColor , unsigned char ledState){

	switch(ledColor){
		case GPIO_RED_LED: switch_ledState(ledColor,ledState);break;							//Choose RED LED to set ON/OFF depending on LedState
		case GPIO_BLUE_LED: switch_ledState(ledColor,ledState);break;							//Choose BlUE LED to set ON/OFF depending on LedState
		case GPIO_GREEN_LED: switch_ledState(ledColor,ledState);break;						//Choose GREEN LED to set ON/OFF depending on LedState
		default: break;
	}		
}

//Function to get state of switches (if 0 is returned then the switch is pressed, otherwise it's not pressed)
unsigned char get_Switch_value(unsigned char which_sw){
	switch(which_sw){
		case GPIO_SW1: return GET_BIT(GPIO_PORTF_DATA_R,GPIO_SW1);break;					//Read SW1 (pin4 in PortF)
		case GPIO_SW2: return GET_BIT(GPIO_PORTF_DATA_R,GPIO_SW2);break;					//Read SW2 (pin0 in PortF)
		default: return 0;
	}
}



void set_led(float d){
	//turn off all LEDs if the total covered distance is less than 95m 
if (d<95) {
	GPIO_set_LEDs_value(GPIO_BLUE_LED , GPIO_LED_OFF);
	GPIO_set_LEDs_value(GPIO_GREEN_LED , GPIO_LED_OFF);
GPIO_set_LEDs_value(GPIO_RED_LED , GPIO_LED_ON);}
//turn ON BLUE LED if the total covered distance is more than or equals 95m and less than 100m
	else if(((95<d)&&(d<100))||d==95){
	GPIO_set_LEDs_value(GPIO_GREEN_LED , GPIO_LED_OFF);
GPIO_set_LEDs_value(GPIO_RED_LED , GPIO_LED_OFF);
	GPIO_set_LEDs_value(GPIO_BLUE_LED , GPIO_LED_ON);}
	//turn ON GREEN LED if the total covered distance is more than 100m
	else  {
	GPIO_set_LEDs_value(GPIO_BLUE_LED , GPIO_LED_OFF);
GPIO_set_LEDs_value(GPIO_RED_LED , GPIO_LED_OFF);
		GPIO_set_LEDs_value(GPIO_GREEN_LED , GPIO_LED_ON);}
}
	
