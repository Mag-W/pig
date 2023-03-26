#include "24C02.h"


void AT24C02_Write(uint8_t address,uint8_t date)
{
	I2C_Start();
	write_byte(AT24C02_Address_W);
	read_ACK();
	write_byte(address);
	read_ACK();
	write_byte(date);
	read_ACK();
	I2C_Stop();
}

uint8_t AT24C02_Read(uint8_t address)
{
	uint8_t dat;
	I2C_Start();
	write_byte(AT24C02_Address_W);
	read_ACK();
	write_byte(address);
	read_ACK();
	
	I2C_Start();
	write_byte(AT24C02_Address_R);
	read_ACK();
	dat=read_byte();
	return dat;
}


void write_MultipleByte(uint8_t address,uint8_t length,uint8_t *date)    //数据块写入
{ 
	I2C_Start();           
	write_byte(AT24C02_Address_W);      
	read_ACK();         //等待24c02把数据线I2C_SDA拉高,即应答
	write_byte(address);//选择写入的24c02地址    
	read_ACK();
	while(length--)
	{
		write_byte(*date++);
		read_ACK();
	}
	I2C_Stop();
}


void read_MultipleByte(uint8_t *temp,uint8_t address,uint8_t data_size)   //读出多个数据
{
	I2C_Start();
	write_byte(AT24C02_Address_W);
	read_ACK();
	write_byte(address);
	read_ACK();
	
	I2C_Start();
	write_byte(AT24C02_Address_R);
	read_ACK();
	
	while(data_size--)
	{
		*temp++=read_byte();
		send_ACK(!data_size);     //主机应答ACK，当data_size = 1时，发送非应答  主机应答，则继续接受数据；不应答，即表示停止接收
	}
	I2C_Stop();
}



