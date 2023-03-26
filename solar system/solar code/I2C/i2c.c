#include "i2c.h"

void I2C_Init()
{
	SCL_H;
	SDA_H;
}

void I2C_Start()//��ʼ
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


void write_byte(uint8_t date)//д��1���ֽ�
{
	uint8_t i,temp;
	temp = date;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;  //��temp����һλ�����λ������PSW�Ĵ���CY��
		SCL_L;
		
		I2C_SDA=CY;
	
		SCL_H;
		
	}
	SCL_L;
	
	SDA_H;
	
}

uint8_t read_byte()//����һ���ֽ�
{
	uint8_t i,k;
	SCL_L;

	SDA_H;
	for(i=0;i<8;i++)
	{
		SCL_H;
	
		k=(k<<1)|I2C_SDA;//���н����ֽڣ�8λһλһλ�ؽ���
		SCL_L;
		
	}

	return k;
}

void send_ACK(bit b_ACK)     //����Ӧ��ACK����Ӧ��,1��ʾ��Ӧ��0��ʾӦ��
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



void read_ACK()    //�ȴ� 24C02 ��Ӧ ACK
{
	uint8_t t=0;
	SCL_H;
	while((I2C_SDA==1)&&(t<250))t++;    //�ȴ�ACK����ʱ����
	SCL_L;
}



void write_add(uint8_t address,uint8_t date)    //�� 24C02 ��дһ���ֽ�����
{
	I2C_Start();        //��ʼ�ź�
	write_byte(0XA0);    //����дָ��
	read_ACK();        //�ȴ�Ӧ��
	write_byte(address);   //����Ҫд��ĵ�ַ
	read_ACK();            //�ȴ�Ӧ��
	write_byte(date);    //��������
	read_ACK();           //�ȴ�Ӧ��
	I2C_Stop();          //ֹͣ�ź�
}


uint8_t read_add(uint8_t address,bit ACK)  //�� 24C02 �ж������ݣ�����һ���ֽ�
{
	uint8_t date;
	I2C_Start();          //��һ����ʼ�ź�
	write_byte(0XA0);      //����дָ��
	read_ACK();              //�ȴ�Ӧ��
	write_byte(address);     //����Ҫ��ȡ�ĵ�ַ
	read_ACK();              //�ȴ�Ӧ��
	I2C_Start();            //�ڶ�����ʼ�ź�
	write_byte(0XA1);       //���Ͷ�ָ��
	read_ACK();              //�ȴ�Ӧ��
	date=read_byte();      //������
	
	send_ACK(ACK);     //����Ӧ��ACK��Ӧ��
	
	I2C_Stop();          //ֹͣ�ź�
	
	return date;
}

	






