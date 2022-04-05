#include "1602.h"

void write_com(u8 com)//写命令
{
	lcdrs=0;//选择为写命令模式
	lcdrw=0;//选择写
	lcden=0;
	P0=com;
	delayms(5);
	lcden=1;   //给使能端一个脉冲
	delayms(5);
	lcden=0;
}

void write_data(u8 dat)//写命令
{
	lcdrs=1;           //选择为读命令模式
	lcdrw=0;//选择写
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
	write_com(0x38);  //设置为16*2显示，5*7点阵，8位数据口
	write_com(0x0c);  //打开显示，不显示光标
	write_com(0x06);  //写入一个字符之后地址指针自动加1
	write_com(0x01);  //显示清0，数据指针清0
}

void lcd_clear(void)
{
	write_com(0x01);
}

void lcd1602_show_string(u8 x,u8 y,u8 *str)//x,y代表坐标，x的范围为0~15，y的范围为0~1，str为要输出的字符串
{
	u8 i=0;

	if(y>1||x>15)return;//行列参数不对则强制退出

	if(y<1)	//第1行显示
	{	
		while(*str!='\0')//字符串是以'\0'结尾，只要前面有内容就显示
		{
			if(i<16-x)//如果字符长度超过第一行显示范围，则在第二行继续显示
			{
				write_com(0x80+i+x);//第一行显示地址设置	
			}
			else
			{
				write_com(0x40+0x80+i+x-16);//第二行显示地址设置	
			}
			write_data(*str);//显示内容
			str++;//指针递增
			i++;	
		}	
	}
	else	//第2行显示
	{
		while(*str!='\0')
		{
			if(i<16-x) //如果字符长度超过第二行显示范围，则在第一行继续显示
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
							u8 display[]={"0123456789"};     //定义数组，并赋初值
							lcd1602_show_string(0,0,"The value of AD:");//第一行显示
							write_com(0x80+0x40+0x04);
              write_data(display[adc_value/100]);
              write_data(display[adc_value/10%10]);
              write_data(display[adc_value%10]);
}






