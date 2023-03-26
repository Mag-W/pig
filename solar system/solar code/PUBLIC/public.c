#include "public.h"

void delay10us(uint16_t ten_us)
{
	while(ten_us--);	
}


void delayms(uint16_t ms)
{
	uint16_t i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}


void delay1s(void)   //Îó²î 0us
{
    uint8_t a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
           _nop_();  //if Keil,require use intrins.h
}



