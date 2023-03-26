#ifndef _public_H_
#define _public_H_

#include <reg52.h>
#include <intrins.h>
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;	
typedef unsigned long uint32_t;

void delay10us(uint16_t ten_us);
void delayms(uint16_t ms);
void delay1s(void);

#endif


