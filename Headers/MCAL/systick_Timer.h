#include "../../Services/bit_utilies.h"
#include "../../Services/TM4C123.h"

#define NVIC_STCTRL_R             (*((volatile unsigned long *)0xE000E010))
#define NVIC_STCTRL_RELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define NVIC_STCTRL_CURRENT_R     (*((volatile unsigned long *)0xE000E018))

#define MAX_VALUE  0x00FFFFFF;
#define CLOCK_RATE  16000000;

void waitMs();
void waitUs();
void delayMs(int time);
void delayUs(int time);
