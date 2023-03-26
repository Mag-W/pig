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


void write_MultipleByte(uint8_t address,uint8_t length,uint8_t *date)    //���ݿ�д��
{ 
	I2C_Start();           
	write_byte(AT24C02_Address_W);      
	read_ACK();         //�ȴ�24c02��������I2C_SDA����,��Ӧ��
	write_byte(address);//ѡ��д���24c02��ַ    
	read_ACK();
	while(length--)
	{
		write_byte(*date++);
		read_ACK();
	}
	I2C_Stop();
}


void read_MultipleByte(uint8_t *temp,uint8_t address,uint8_t data_size)   //�����������
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
		send_ACK(!data_size);     //����Ӧ��ACK����data_size = 1ʱ�����ͷ�Ӧ��  ����Ӧ��������������ݣ���Ӧ�𣬼���ʾֹͣ����
	}
	I2C_Stop();
}



