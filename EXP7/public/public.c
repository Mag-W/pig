#include "public.h"


void delay10us(u16 ten_us)
{
	while(ten_us--);	
}


void delayms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}

