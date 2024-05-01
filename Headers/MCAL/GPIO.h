
//Switches in Port F

#define GPIO_SW1 4							//Switch 1 bit0 in PortF Data register
#define GPIO_SW2 0							//Switch 2 bit4 in PortF Data register
#define GPIO_NOSW_PRESSED 0


//LEDs in Port F

#define GPIO_RED_LED   1				//RED   LED  bit1 in PortF Data register
#define GPIO_BLUE_LED  2				//BLUE  LED  bit2 in PortF Data register
#define GPIO_GREEN_LED 3				//GREEN LED  bit3 in PortF Data register

//LEDs-state

#define GPIO_LED_ON  1
#define GPIO_LED_OFF 0



void GPIO_PORTF_initialization(void);

void GPIO_PORTB_initialization(void);

void GPIO_PORTE_initialization(void);

void GPIO_set_LEDs_value(unsigned char ledColor , unsigned char ledState);

unsigned char get_Switch_value(unsigned char which_sw);

void switch_ledState(unsigned char ledColor,unsigned char ledState);
void set_led(float d);
