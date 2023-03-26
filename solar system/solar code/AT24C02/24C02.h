#ifndef _24C02_H_
#define _24C02_H_	

#include "i2c.h"


#define AT24C02_Address_R 0xa1 //读地址
#define AT24C02_Address_W 0xa0 //写地址

//注：宏定义的名字第一个字不能是数字!

extern void AT24C02_Write(uint8_t address,uint8_t date);
extern uint8_t AT24C02_Read(uint8_t address);

extern void write_MultipleByte(uint8_t address,uint8_t length,uint8_t *date);//多字节的写入
extern void read_MultipleByte(uint8_t *temp,uint8_t address,uint8_t data_size) ;//多字节的读取
 

#endif 

