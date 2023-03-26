#ifndef _24C02_H_
#define _24C02_H_	

#include "i2c.h"


#define AT24C02_Address_R 0xa1 //����ַ
#define AT24C02_Address_W 0xa0 //д��ַ

//ע���궨������ֵ�һ���ֲ���������!

extern void AT24C02_Write(uint8_t address,uint8_t date);
extern uint8_t AT24C02_Read(uint8_t address);

extern void write_MultipleByte(uint8_t address,uint8_t length,uint8_t *date);//���ֽڵ�д��
extern void read_MultipleByte(uint8_t *temp,uint8_t address,uint8_t data_size) ;//���ֽڵĶ�ȡ
 

#endif 

