/* Created by:               Mag.W
** Created date:             2022/05/30
** The last updated date:    2022/6/14
** Version:                  1.0
*/

#include "reg52.h"
#include "oled.h"
#include "ADC.h"
#include "string.h"
#include "stdio.h"
#include "servo.h"
#include <math.h>
#include "24C02.h"
sbit beep = P1^2;
sbit PWM0 = P2^0;
sbit PWM1 = P2^1;                                                                                                             
//#define Vol_H(x) (uint16_t)ceil(65536-((10.24*x+461)))//�ߵ�ƽ����
//#define Vol_L(x) (uint16_t)ceil(65536-((18432-(10.24*x+461))))//�͵�ƽ����
#define Vol_H(x) (uint16_t)(65536-(10*x+461))//�ߵ�ƽ�������˷�����΢�����Ϊ0.24*x/10.24��
#define Vol_L(x) (uint16_t)(65536-(18432-(10*x+461)))//�͵�ƽ����
float  adc_val[5];
uint8_t code adc_chx[5]={ADC_CH0,ADC_CH1,ADC_CH2,ADC_CH3,ADC_CH4};

uint8_t T0_flag,T1_flag;
uint8_t angle0=5;//��������ʼ����5��λ��---0-90
uint8_t angle1=90;//��������ʼ����90��λ��---0-180
void Angle_Chg(void);
void timer_init()//T0��T1��ʱ����ʼ��
{
	/*0.5ms------65536-461  0��
	  2.5ms------65536-2304 180��
	  ת��a��-----65536-int(10.24*a+461)
	  ���һ������Ϊ20ms------65536-18432
		һ������ʣ�µĵ͵�ƽ����Ϊ65536-��18432-int��10.24*a+461����
	  */
	TMOD=0X11;//������ʱ���������ڷ�ʽ1
  TH0=Vol_H(angle0)/256;   // 
	TL0=Vol_H(angle0)%256;   
  TH1=Vol_H(angle1)/256;   // 
	TL1=Vol_H(angle1)%256;   
	EA=1;
	ET0=1;
	ET1=1;
	TR0=1;
	TR1=1;
}


void main()
{
	  uint8_t test=0;
    OLED_Init();			//��ʼ��OLED  
   	
	  delayms(1000);
		AT24C02_Write(0x00,0x00);
	  delayms(100);
	  OLED_ShowString(12,9,"SOLAR SYSTEME: ",16);
	  OLED_ShowString(0,13,"DESIGNED BY: ",12);
		OLED_ShowString(80,15,"MAG.W",12);
	  delayms(1000);
		timer_init();
	// OLED_Clear();
   // GUI_Axis();
	//GUI_Clear();
  //OLED_Refresh();
 // OLED_Clear();

	while(1)
	{
	 uint8_t i,j;
		for(i=0;i<5;i++)
		{
			adc_val[i]=ADS7830_GetADC_CHx(adc_chx[i]);
			}
			/*
			if(adc_val[4]>5&&adc_val[4]<50)//��Դ��ѹ����
			{
				for(j=0;j<5;j++)
				{
					beep=~beep;
					delayms(100);
				}
			}
			*/
		
		Angle_Chg();//׷�⺯��
	/*
		OLED_ShowNum(10,0,adc_val[0],3,12);
		OLED_ShowNum(50,0,adc_val[1],3,12);
		OLED_ShowNum(10,2,adc_val[2],3,12);
		OLED_ShowNum(50,2,adc_val[3],3,12);
    OLED_ShowNum(50,4,adc_val[4],3,12);
	   */                                                              
				//test=AT24C02_Read(2);
		//OLED_ShowNum(10,0,test,3,12);
		
	}

}

void 	T0_time() interrupt 1//����������������
{
	if(T0_flag)
	{
		TH0=(Vol_H(angle0))/256;   // 
  	TL0=(Vol_H(angle0))%256;   //
		PWM0=1;
	}
	else{
	  TH0=(Vol_L(angle0))/256;   // 
  	TL0=(Vol_L(angle0))%256;   //
		PWM0=0;
	}
	
	T0_flag=~T0_flag;
}

void T1_time() interrupt 3//����������������
{
	if(T1_flag)
	{
		TH1=(Vol_H(angle1))/256;   // 
  	TL1=(Vol_H(angle1))%256;   //
		PWM1=1;
	}
	else{
	  TH1=(Vol_L(angle1))/256;   // 
  	TL1=(Vol_L(angle1))%256;   //
		PWM1=0;
	}
	T1_flag=~T1_flag;
}


void Angle_Chg()
{
  if(abs(adc_val[0]-adc_val[1])>10)//��������ת��
	{
		if((adc_val[0]-adc_val[1])>10)
		{	
			angle0-=1;
			if(angle0<8)angle0=8;
		}
		else 
		{
			angle0+=1;		
		
			if(angle0>80)angle0=80;
		}
	}
	
	 if(abs(adc_val[2]-adc_val[3])>10)//����������ת
	{
		if((adc_val[2]-adc_val[3])>10)
		{
			angle1-=1;
			if(angle1<5)angle1=5;
		}
		else 
		{
			angle1+=1;		
		
			if(angle1>175)angle1=175;
		}
	}
}


