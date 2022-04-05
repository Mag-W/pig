#ifndef _CALCULATE_H
#define _CALCULATE_H

#include "1602.h"
#include "key.h"

extern u8 code mat[];
extern u16 sum1,sum2;
extern sum3 ; //用于除法
extern u8 addflag,subflag,mulflag,divflag;
extern u8 keyflag; //	在keyvaluechuli()函数中控制
extern u8 flag;// 控制乘中的sum1;

void data_process(void);
void add(void);
void sub(void);
void mul(void);
void div(void);
void equal(void);
void cal(void);


#endif