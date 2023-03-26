#ifndef _I2C_H_
#define _I2C_H_

#include "public.h"

sbit I2C_SCL=P1^0;
sbit I2C_SDA=P1^1;
 
 
#define SCL_H I2C_SCL=1
#define SCL_L I2C_SCL=0

#define SDA_H I2C_SDA=1
#define SDA_L I2C_SDA=0



extern void I2C_Init();
extern void I2C_Start();
extern void I2C_Stop();
extern void read_ACK();
extern void send_ACK(bit ACK);//1表示非应答，0表示应答
   
extern void write_byte(unsigned char date);
extern unsigned char read_byte();
extern void write_add(unsigned char address,unsigned char date);
extern unsigned char read_add(unsigned char address,bit ACK);

#endif


