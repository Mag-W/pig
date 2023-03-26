#include "adc.h"
#include "i2c.h"


uint8_t ADS7830_GetADC_CHx(uint8_t ADC_CHx)
{
	uint8_t dat;
	I2C_Start();
	write_byte(0x90);//�����豸д��ַ
	read_ACK();
	write_byte(ADC_CHx);//���Ϳ����ֽ�
	read_ACK();
	I2C_Stop();
	
	I2C_Start();
	write_byte(0x91);//�����豸����ַ
	read_ACK();
	dat=read_byte();
	send_ACK(1);//�������ͷ�Ӧ���ź�
	I2C_Stop();
	return dat;
}



