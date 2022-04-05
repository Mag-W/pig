#ifndef _LCD1602_H
#define _LCD1602_H

#include "public.h"

sbit lcdrs=P2^6;//数据命令选择
sbit lcdrw=P2^5;//读写选择
sbit lcden=P2^7; //使能信号

void write_com(u8 com);
void write_data(u8 dat);
void lcd_init(void);
void lcd_clear(void);
void lcd1602_show_string(u8 x,u8 y,u8 *str);
void AD_Display(u8 adc_value);
#endif
