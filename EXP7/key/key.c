#include "key.h"

u8 key_status1=0;
u8 key_status2=0;
u8 key_flag1=0;//作为独立按键按下的标志位；
u8 key_flag=0;//作为矩阵键盘按下的标志位

void key_scan(void)//独立按键
{
		if(key1==0)
	{
		delayms(10);//延时消抖
		if(key1==0)
		{
			key_status1=1;
		  key_flag1=1;
			while(!key1);//等待按键松开
		}
	}
	
	else if(key2==0)
	{
		delayms(10);
		if(key2==0)
		{
			key_status1=2;
			key_flag1=1;
			while(!key2);
		}
	}
	
	else if(key3==0)
	{
		delayms(10);
		if(key3==0)
		{
			key_status1=3;
			key_flag1=1;
			while(!key3);
		}
		
		else if(key4==0)
	{
		delayms(10);
		if(key4==0)
		{
			key_status1=4;
			key_flag1=1;
			while(!key4);
		}
  }	
}
}



void matrixkeyscan()
{
	u8 temp;
	//检测第一行
	P1=0x7f;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//确保第一排有按键被按下
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//确保第一排有按键被按下
		{
			key_flag=1;
		  temp=P1;    //因为按键按下P2的值被改变
			switch(temp)
			{
				case 0x77:key_status2=0;//第一个按键（即P13）被按下，P13被置为低电平
				break;
				case 0x7b:key_status2=1;
				break;
				case 0x7d:key_status2=2;
				break;
				case 0x7e:key_status2=3;
				break;
				default:break;
			}
			while(temp!=0x0f)//等待按键释放
			{
				temp=P1;//一直将检测到的P1的值赋给temp
				temp=temp&0x0f;
			}
		}
  }
	
	//检测第二行
	P1=0xbf;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//确保第一排有按键被按下
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//确保第一排有按键被按下
		{
			key_flag=1;
		  temp=P1;    //因为按键按下P2的值被改变
			switch(temp)
			{
				case 0xb7:key_status2=4;//第一个按键（即P13）被按下，P13被置为低电平
				break;
				case 0xbb:key_status2=5;
				break;
				case 0xbd:key_status2=6;
				break;
				case 0xbe:key_status2=7;
				break;
				default:break;
			}
			while(temp!=0x0f)//等待按键释放
			{
				temp=P1;//一直将检测到的P1的值赋给temp
				temp=temp&0x0f;
			}
		}
  }
	
	//检测第三行
	P1=0xdf;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//确保第一排有按键被按下
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//确保第一排有按键被按下
		{
			key_flag=1;
		  temp=P1;    //因为按键按下P2的值被改变
			switch(temp)
			{
				case 0xd7:key_status2=8;//第一个按键（即P13）被按下，P13被置为低电平
				break;
				case 0xdb:key_status2=9;
				break;
				case 0xdd:key_status2=10;
				break;
				case 0xde:key_status2=11;
				break;
				default:break;
			}
			while(temp!=0x0f)//等待按键释放
			{
				temp=P1;//一直将检测到的P1的值赋给temp
				temp=temp&0x0f;
			}
		}
  }
	
	//检测第四行
	P1=0xef;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//确保第一排有按键被按下
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//确保第一排有按键被按下
		{
			key_flag=1;
		  temp=P1;    //因为按键按下P2的值被改变
			switch(temp)
			{
				case 0xe7:key_status2=12;//第一个按键（即P13）被按下，P13被置为低电平
				break;
				case 0xeb:key_status2=13;
				break;
				case 0xed:key_status2=14;
				break;
				case 0xee:key_status2=15;
				break;
				default:break;
			}
			while(temp!=0x0f)//等待按键释放
			{
				temp=P1;//一直将检测到的P1的值赋给temp
				temp=temp&0x0f;
			}
		}
  }
}

	