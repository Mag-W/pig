/* Created by:               Mag.W
** Created date:             2022/3/22
** Version:                  2.0
*/
#include <reg52.h>
#define uint unsigned int 
#define uchar unsigned char
unsigned char code table[]={0x3f,0x06,0x5b,0x4f,
														0x66,0x6d,0x7d,0x07,
														0x7f,0x6f,0x77,0x7c,
														0x39,0x5e,0x79,0x71};
unsigned char code led_control[]={0x1c,0x18,0x14,
																	0x10,0x0c,0x08,
	                                0x04,0x00};//P2�ڿ�������һ����
sbit key1 = P3 ^ 1;//����1,��Ϊ�����ļ�
sbit key2 = P3 ^ 0;//����2����Ϊ�����ļ�				
sbit key3 = P3 ^ 2;//����3����Ϊ�����Ŀ�ʼ
sbit key4 = P3 ^ 3;//����4����Ϊ��������ͣ
sbit beep = P1 ^ 5;//��������																	
uchar cnt;//ÿ20ms������һ
uchar num=5;//��Ϊ��ʱʱ�䣬����������λ��
uchar a;//��Ϊ������ʮλ
uchar b;//��Ϊ�����ĸ�λ
uchar key_status;//����״̬
int key_scan();
void init(void);																	
void delayms(uint xms);
void main()
{
	init();
	ET0=1;
	while(1)
	{
		
		switch(key_scan())
		{
			case 1:{
				num+=5;
				while(key1==0);
				if(num>=60)num=60;
			}
				break;
			
			case 2:{
			num-=5;
				while(key2==0);
			if(num<=5)num=5;
			}
			break;
			
			case 3:
			{
				TR0=1;
				EA=1;
				while(key3==0);
			}
			break;
			
			case 4: 
				{ 
				 TR0=0;
					while(key4==0);
			}
			break;
			
			default:break;
		}
		a=num/10;
		b=num%10;
		
		P2=led_control[1];
		P0=0xff;
		P0=table[a];
		delayms(1);
		
		
		P2=led_control[2];
		P0=0xff;
		P0=table[b];
		delayms(1);
		
		if(num==0)
		{
			uint i=1000;
			TR0=0;
		
			for(i;i>0;i--)
			{
			beep=!beep;
			delayms(1);
			}
			num=5;
		}
	}
}	

int key_scan()
{
		if(key1==0)
	{
		delayms(10);//��ʱ����
		if(key1==0)
		{
			key_status=1;
			return 1;
			while(!key1);//�ȴ������ɿ�
		}
	}
	
	else if(key2==0)
	{
		delayms(10);
		if(key2==0)
		{
			key_status=2;
			return 2;
			while(!key2);
		}
	}
	
	else if(key3==0)
	{
		delayms(10);
		if(key3==0)
		{
			key_status=3;
			return 3;
			while(!key3);
		}
		
		else if(key4==0)
	{
		delayms(10);
		if(key4==0)
		{
			key_status=4;
			return 4;
			while(!key4);
		}
}	
}
	}
void init()
{
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
}

void T0_time() interrupt 1
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	cnt++;
	if(cnt==20)//ÿ50ms*20�ж�һ��
	{
		cnt=0;//��������
		num--;
	}
		
}

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}																	