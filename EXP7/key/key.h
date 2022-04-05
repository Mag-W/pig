#ifndef _KEY_H
#define _KEY_H

#include "public.h"
sbit key1 = P3 ^ 1;
sbit key2 = P3 ^ 0;			
sbit key3 = P3 ^ 2;
sbit key4 = P3 ^ 3;


extern u8 key_status1;//独立键盘
extern u8 key_status2;//矩阵键盘
extern u8 key_flag1;
extern u8 key_flag;//作为判断矩阵键盘有按下的标志位
void key_scan(void);
void matrixkeyscan(void);

#endif