# include "../../Services/bit_utilies.h "
# include "../../Services/TM4C123.h "
# include "../../Headers/MCAL/UART.h"


//Use PortA for UART0 for serial communication between pc and TivaC
void UART0_Initialaize (){ 
	 SET_BIT(SYSCTL_RCGCGPIO_R,PortA);										//Activate PortA to use A0 & A1 as Rx & tx respectively for UART0
	 while(GET_BIT(SYSCTL_PPGPIO_R,PortA)==0){};	 				//Wait for clock stabilization
	   SET_BIT(SYSCTL_RCGCUART_R,UATR0);									//Activate UART0
	 while(GET_BIT(SYSCTL_PPUART_R,UATR0)==0){};					//Wait for stabilization
		 CLR_BIT(UART0_CTL_R,enableUART);										//Disbale UART0 to make configurations first
		 //Baud rate = clock freq (16Mhz) / (16* (IBRD + ( (FBRD-0.5)/ 64 )) ) = 9600
	   SET(UART0_IBRD_R,104);															//Integer Baud rate = 104 ( int( 16Mhz /(16*Baud rate) ) )
	 	 SET(UART0_FBRD_R,11);															//Float Baud rate = 11	  int( ( 16Mhz /(16*Baud rate)- IBRD ) *64 + 0.5
	 	 SET(GPIO_PORTA_AFSEL_R,PA0AndPA1);									//Enable alternate func for A0 & A1
	 	 SET(GPIO_PORTA_PCTL_R,17);													//choose UART as alternate function for A0 & A1
	 	 SET(GPIO_PORTA_DEN_R,PA0AndPA1);										//set A0 & A1 as digital pins
	 	 SET(GPIO_PORTA_AMSEL_R,noAnalog);									//Disbale analog configuration for pins A0 & A1
	 	 SET(UART0_LCRH_R,enableFIFOAnd8BitsAndOneStop);		//Enable FIFO, choose data length 8 bits in data frame and choose one stop bit
	   SET(UART0_CTL_R,enableUARTAndRXAndTX);							//Enable UART again after all configurations have been set
 }
 
 //Function to allow for Rx to receive data correctly after checking if there is avaliable data in its buffer, then return recieved data
char UART0_Receiver(void)  
{
    char data;
	  while((UART0_FR_R & (1<<4)) != 0){}; 							/* wait until Rx FIFO buffer is not empty(contains data) so that Rx can receive and store this data */
    data = UART0_DR_R ;  															
    return (unsigned char) data; 
}
//Function to allow Tx to send data correctly after checking if there is avaliable space in its buffer
//Sends data in char
void UART0_Transmitter(unsigned char data)  
{
    while((UART0_FR_R & (1<<5)) != 0); 								/* wait until Tx FIFO buffer not full so that it can receive more data in the buffer then UART can send it */
    UART0_DR_R = data;                  
}
//Works like UART0_Transmitter but sends data as string instead
void UART0_printstring(char *str)
{
  while(*str)
	{
		UART0_Transmitter(*(str++));
	}
}



 //Use PortE for UART7 for serial communication between GPS module and TivaC
 void UART7_Initialaize (){                                  
	   SET_BIT(SYSCTL_RCGCUART_R,UATR7);												//Activate PortA to use E0 & E1 as Rx & tx respectively for UART7
	 while(GET_BIT(SYSCTL_PPUART_R,UATR7)==0){};								//Wait for clock stabilization
	 	 SET_BIT(SYSCTL_RCGCGPIO_R,PortE);												//Activate UART7
	 while(GET_BIT(SYSCTL_PPGPIO_R,PortE)==0){};								//Wait for stabilization
		 CLR_BIT(UART7_CTL_R,0);																	//Disbale UART7 to make configurations first
		 //Baud rate = clock freq (16Mhz) / (16* (IBRD + ( (FBRD-0.5)/ 64 )) ) = 9600
	   SET(UART7_IBRD_R,104);																		//Integer Baud rate = 104 ( int( 16Mhz /(16*Baud rate) ) )
	 	 SET(UART7_FBRD_R,11);																		//Float Baud rate = 11	  int( ( 16Mhz /(16*Baud rate)- IBRD ) *64 + 0.5
	 	 SET(GPIO_PORTE_AFSEL_R,PE4AndPE5);												//Enable alternate func for E0 & E1
	 	 SET(GPIO_PORTE_PCTL_R,17);																//choose UART as alternate function for E0 & E1
	 	 SET(GPIO_PORTE_DEN_R,PE4AndPE5);													//set E0 & E1 as digital pins
	 	 SET(GPIO_PORTE_AMSEL_R,noAnalog);												//Disbale analog configuration for pins E0 & E1
	 	 SET(UART7_LCRH_R,enableFIFOAnd8BitsAndOneStop);					//Enable FIFO, choose data length 8 bits in data frame and choose one stop bit
	   SET(UART7_CTL_R,enableUARTAndRXAndTX);										//Enable UART again after all configurations have been set
 }


//Function to check for Rx to receive data correctly after checking if there is avaliable data in its buffer, then return recieved data
char UART7_Receiver(void)  
{
    char data;
	  while((UART7_FR_R & (1<<4)) != 0){}; 				/* wait until Rx FIFO buffer is not empty(contains data) so that Rx can receive and store this data */
    data = UART7_DR_R ;  	
			//UART7_Transmitter(data);
    return (unsigned char) data; 
}
//Function to allow Tx to send data correctly after checking if there is avaliable space in its buffer
//Sends data in char
void UART7_Transmitter(unsigned char data)  
{
    while((UART7_FR_R & (1<<5)) != 0); 					/* wait until Tx FIFO buffer not full so that it can receive more data in the buffer then UART can send it */			
    UART0_DR_R = data;                  				
}
//Works like UART7_Transmitter but sends data as string instead
void UART7_printstring(char *str)
{
  while(*str)
	{
		UART7_Transmitter(*(str++));
	}
}

