#include "i2c.h"

void I2C_Init()
{
	SCL_H;
	SDA_H;
}

void I2C_Start()//起始
{
	SCL_H;
	SDA_H;
	
	SDA_L;
	SCL_L;
}

void I2C_Stop()
{
	SCL_H;
	SDA_L;
	SDA_H;
}


void write_byte(uint8_t date)//写入1个字节
{
	uint8_t i,temp;
	temp = date;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;  //将temp左移一位，最高位将移入PSW寄存器CY中
		SCL_L;
		
		I2C_SDA=CY;
	
		SCL_H;
		
	}
	SCL_L;
	
	SDA_H;
	
}

uint8_t read_byte()//读出一个字节
{
	uint8_t i,k;
	SCL_L;

	SDA_H;
	for(i=0;i<8;i++)
	{
		SCL_H;
	
		k=(k<<1)|I2C_SDA;//串行接收字节，8位一位一位地接受
		SCL_L;
		
	}

	return k;
}

void send_ACK(bit b_ACK)     //主机应答ACK，或不应答,1表示非应答，0表示应答
{
	SCL_L;
	if(b_ACK)                    //ACK
	{
		SDA_H;        
	}
	else                          //ACK
	{
		SDA_L;
	}
	
	SCL_H;
	SCL_L;
}



void read_ACK()    //等待 24C02 回应 ACK
{
	uint8_t t=0;
	SCL_H;
	while((I2C_SDA==1)&&(t<250))t++;    //等待ACK，超时跳出
	SCL_L;
}



void write_add(uint8_t address,uint8_t date)    //向 24C02 中写一个字节数据
{
	I2C_Start();        //起始信号
	write_byte(0XA0);    //发送写指令
	read_ACK();        //等待应答
	write_byte(address);   //发送要写入的地址
	read_ACK();            //等待应答
	write_byte(date);    //发送数据
	read_ACK();           //等待应答
	I2C_Stop();          //停止信号
}


uint8_t read_add(uint8_t address,bit ACK)  //从 24C02 中读出数据，读出一个字节
{
	uint8_t date;
	I2C_Start();          //第一次起始信号
	write_byte(0XA0);      //发送写指令
	read_ACK();              //等待应答
	write_byte(address);     //发送要读取的地址
	read_ACK();              //等待应答
	I2C_Start();            //第二次起始信号
	write_byte(0XA1);       //发送读指令
	read_ACK();              //等待应答
	date=read_byte();      //读数据
	
	send_ACK(ACK);     //主机应答ACK或不应答
	
	I2C_Stop();          //停止信号
	
	return date;
}

	






