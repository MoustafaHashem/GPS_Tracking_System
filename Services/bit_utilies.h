#include <stdint.h>

#ifndef Bit_Utilies
#define Bit_Utilies

#define GET_BIT(reg1,bit)   ((reg1>>bit)&1)
#define GET_REG(reg)        (reg&0xff)

#define SET(reg,val)        reg |= val
#define SET_BIT(reg,bit)    reg |= (1<<bit)

#define CLR(reg,val)        reg &=~val
#define CLR_BIT(reg,val)    reg &=~(1<<val)

#define HWREG(x)                                                              \
        (*((volatile uint32_t *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile uint16_t *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile uint8_t *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                     \
              (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
               (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
               (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#endif