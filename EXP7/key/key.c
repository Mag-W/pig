#include "key.h"

u8 key_status1=0;
u8 key_status2=0;
u8 key_flag1=0;//��Ϊ�����������µı�־λ��
u8 key_flag=0;//��Ϊ������̰��µı�־λ

void key_scan(void)//��������
{
		if(key1==0)
	{
		delayms(10);//��ʱ����
		if(key1==0)
		{
			key_status1=1;
		  key_flag1=1;
			while(!key1);//�ȴ������ɿ�
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
	//����һ��
	P1=0x7f;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//ȷ����һ���а���������
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//ȷ����һ���а���������
		{
			key_flag=1;
		  temp=P1;    //��Ϊ��������P2��ֵ���ı�
			switch(temp)
			{
				case 0x77:key_status2=0;//��һ����������P13�������£�P13����Ϊ�͵�ƽ
				break;
				case 0x7b:key_status2=1;
				break;
				case 0x7d:key_status2=2;
				break;
				case 0x7e:key_status2=3;
				break;
				default:break;
			}
			while(temp!=0x0f)//�ȴ������ͷ�
			{
				temp=P1;//һֱ����⵽��P1��ֵ����temp
				temp=temp&0x0f;
			}
		}
  }
	
	//���ڶ���
	P1=0xbf;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//ȷ����һ���а���������
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//ȷ����һ���а���������
		{
			key_flag=1;
		  temp=P1;    //��Ϊ��������P2��ֵ���ı�
			switch(temp)
			{
				case 0xb7:key_status2=4;//��һ����������P13�������£�P13����Ϊ�͵�ƽ
				break;
				case 0xbb:key_status2=5;
				break;
				case 0xbd:key_status2=6;
				break;
				case 0xbe:key_status2=7;
				break;
				default:break;
			}
			while(temp!=0x0f)//�ȴ������ͷ�
			{
				temp=P1;//һֱ����⵽��P1��ֵ����temp
				temp=temp&0x0f;
			}
		}
  }
	
	//��������
	P1=0xdf;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//ȷ����һ���а���������
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//ȷ����һ���а���������
		{
			key_flag=1;
		  temp=P1;    //��Ϊ��������P2��ֵ���ı�
			switch(temp)
			{
				case 0xd7:key_status2=8;//��һ����������P13�������£�P13����Ϊ�͵�ƽ
				break;
				case 0xdb:key_status2=9;
				break;
				case 0xdd:key_status2=10;
				break;
				case 0xde:key_status2=11;
				break;
				default:break;
			}
			while(temp!=0x0f)//�ȴ������ͷ�
			{
				temp=P1;//һֱ����⵽��P1��ֵ����temp
				temp=temp&0x0f;
			}
		}
  }
	
	//��������
	P1=0xef;
	temp=P1;
	temp=temp&0x0f;
	if(temp!=0x0f)//ȷ����һ���а���������
	{
		delayms(10);
		temp=P1;
		temp=temp&0x0f;
		if(temp!=0x0f)//ȷ����һ���а���������
		{
			key_flag=1;
		  temp=P1;    //��Ϊ��������P2��ֵ���ı�
			switch(temp)
			{
				case 0xe7:key_status2=12;//��һ����������P13�������£�P13����Ϊ�͵�ƽ
				break;
				case 0xeb:key_status2=13;
				break;
				case 0xed:key_status2=14;
				break;
				case 0xee:key_status2=15;
				break;
				default:break;
			}
			while(temp!=0x0f)//�ȴ������ͷ�
			{
				temp=P1;//һֱ����⵽��P1��ֵ����temp
				temp=temp&0x0f;
			}
		}
  }
}

	