#ifndef _LCD1602_H
#define _LCD1602_H

#include "public.h"

sbit lcdrs=P2^6;//��������ѡ��
sbit lcdrw=P2^5;//��дѡ��
sbit lcden=P2^7; //ʹ���ź�

void write_com(u8 com);
void write_data(u8 dat);
void lcd_init(void);
void lcd_clear(void);
void lcd1602_show_string(u8 x,u8 y,u8 *str);
void AD_Display(u8 adc_value);
#endif
