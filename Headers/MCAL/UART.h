// U0RX  PA0
// U0TX  PA1
// U5RX  PE0
// U5TX  PE1
// UART EN P0
#define UATR0                           0
#define UATR7                           7
#define PortA                           0
#define PortE                           4
#define busClockFrequency               (16*(10^6))
#define divider                         (9600)
#define bitRate                         ((busClockFrequency)/(16*divider))
#define IntegerOfBR                     (int)bitRate
#define floatOfBR                       (int)(((bitRate-(int)bitRate)*64)+0.5)
#define PA0AndPA1                        3
#define PE4AndPE5                        3
#define PA00AndPA10                      17
#define PE40AndPE50                      17
#define enableFIFOAnd8BitsAndOneStop     112
#define noAnalog                         0
#define enableUARTAndRX                 513  
#define enableUARTAndRXAndTX            769
#define enableUART                       0
void UART0_Initialaize ();
char UART0_Receiver(void);
void UART0_Transmitter(unsigned char data);
void UART0_printstring(char *str);
void UART7_Initialaize ();
char UART7_Receiver(void);
void UART7_Transmitter(unsigned char data);
void UART7_printstring(char *str);
 



