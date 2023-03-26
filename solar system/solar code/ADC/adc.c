#include "adc.h"
#include "i2c.h"


uint8_t ADS7830_GetADC_CHx(uint8_t ADC_CHx)
{
	uint8_t dat;
	I2C_Start();
	write_byte(0x90);//发送设备写地址
	read_ACK();
	write_byte(ADC_CHx);//发送控制字节
	read_ACK();
	I2C_Stop();
	
	I2C_Start();
	write_byte(0x91);//发送设备读地址
	read_ACK();
	dat=read_byte();
	send_ACK(1);//主机发送非应答信号
	I2C_Stop();
	return dat;
}



