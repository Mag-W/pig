#include "1602.h"

void write_com(u8 com)//д����
{
	lcdrs=0;//ѡ��Ϊд����ģʽ
	lcdrw=0;//ѡ��д
	lcden=0;
	P0=com;
	delayms(5);
	lcden=1;   //��ʹ�ܶ�һ������
	delayms(5);
	lcden=0;
}

void write_data(u8 dat)//д����
{
	lcdrs=1;           //ѡ��Ϊ������ģʽ
	lcdrw=0;//ѡ��д
	lcden=0;
	P0=dat;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}

void lcd_init(void)
{
	lcden=0;
	write_com(0x38);  //����Ϊ16*2��ʾ��5*7����8λ���ݿ�
	write_com(0x0c);  //����ʾ������ʾ���
	write_com(0x06);  //д��һ���ַ�֮���ַָ���Զ���1
	write_com(0x01);  //��ʾ��0������ָ����0
}

void lcd_clear(void)
{
	write_com(0x01);
}

void lcd1602_show_string(u8 x,u8 y,u8 *str)//x,y�������꣬x�ķ�ΧΪ0~15��y�ķ�ΧΪ0~1��strΪҪ������ַ���
{
	u8 i=0;

	if(y>1||x>15)return;//���в���������ǿ���˳�

	if(y<1)	//��1����ʾ
	{	
		while(*str!='\0')//�ַ�������'\0'��β��ֻҪǰ�������ݾ���ʾ
		{
			if(i<16-x)//����ַ����ȳ�����һ����ʾ��Χ�����ڵڶ��м�����ʾ
			{
				write_com(0x80+i+x);//��һ����ʾ��ַ����	
			}
			else
			{
				write_com(0x40+0x80+i+x-16);//�ڶ�����ʾ��ַ����	
			}
			write_data(*str);//��ʾ����
			str++;//ָ�����
			i++;	
		}	
	}
	else	//��2����ʾ
	{
		while(*str!='\0')
		{
			if(i<16-x) //����ַ����ȳ����ڶ�����ʾ��Χ�����ڵ�һ�м�����ʾ
			{
				write_com(0x80+0x40+i+x);	
			}
			else
			{
				write_com(0x80+i+x-16);	
			}
			write_data(*str);
			str++;
			i++;	
		}	
	}				
}

void AD_Display(u8 adc_value)
{
							u8 display[]={"0123456789"};     //�������飬������ֵ
							lcd1602_show_string(0,0,"The value of AD:");//��һ����ʾ
							write_com(0x80+0x40+0x04);
              write_data(display[adc_value/100]);
              write_data(display[adc_value/10%10]);
              write_data(display[adc_value%10]);
}






