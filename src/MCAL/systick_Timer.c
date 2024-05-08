#include "../../Headers/MCAL/systick_Timer.h"
#include "../../Services/bit_utilies.h"
#include "../../Services/TM4C123.h "

void waitMs() {
    NVIC_ST_CTRL_R =0;
    NVIC_ST_RELOAD_R =16000-1;
    NVIC_ST_CURRENT_R =0;
    NVIC_ST_CTRL_R =0x05;
    while((NVIC_ST_CTRL_R & 0x00010000)==0);
    }

void waitUs() {
    NVIC_ST_CTRL_R =0;
    NVIC_ST_RELOAD_R =16-1;
    NVIC_ST_CURRENT_R =0;
    NVIC_ST_CTRL_R =0x05;
    while((NVIC_ST_CTRL_R & 0x00010000)==0);
    }

void delayMs(int time){
    int i;
    for(i=0;i<time;i++) waitMs();
}

void delayUs(int time){
    int i ;
    for(i=0;i<time;i++){
        waitUs();
    }
}
