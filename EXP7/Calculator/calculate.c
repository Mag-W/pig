#include "calculate.h"

u8 code  mat[]={'0','1','2','3','4','5','6','7','8','9','+','-','*','/','='};

u16 sum1,sum2;
float sum3 ; //���ڳ���
u8 addflag,subflag,mulflag,divflag;
u8 keyflag; //	��keyvaluechuli()�����п���
u8 flag ;// ���Ƴ��е�sum1;


void data_process()  //  0~9
{
   if(key_status2==15)//key15��Ϊ�����
   { 
    write_com(0x01);
	 sum1=sum2=0;
	 addflag=0;
	 subflag=0;
	 mulflag=0;
	 divflag=0;	 
   }
   if(key_status2<10)//������0-9����
   {
     if(flag==1)   //flag�ڳ��п���ʹ����һ���������sum1
	 {
	  sum1=0;
	  flag=0;
	 }
	  sum1=sum1*10+key_status2;
	  write_data(mat[key_status2]);//�������������ʾ
   }
}




void add(void)
{
  addflag++;//�ӷ���־λ��1
  subflag=mulflag=divflag=0;//������־λ����
  sum2=sum1; //���������sum1�͸�sum2����
  sum1=0;   //����
}

void sub(void)
{
	subflag++;
	addflag=mulflag=divflag=0;
	sum2=sum1; 
	sum1=0;
}

void mul(void)
{
	mulflag++;
	addflag=subflag=divflag=0;
	sum2=sum1;
	flag=1;
	sum1=0;
}

void div(void)
{
 divflag++;
	addflag=subflag=mulflag=0;
	sum3=sum1;
	sum1=0;
}



void equal(void)//�������Ľ��
{
	if(addflag)
	{
		sum2+=sum1;
		write_com(0x80+0x4f);//�ڶ������ұ߿�ʼ
		write_com(0x04);//ÿ����һ���ַ���������һλ
		
		while(sum2!=0)//��sumÿһλ���ӵ�λ�������
		{
			write_data(0x30+sum2%10);//ת��Ϊasccii�����
			sum2/=10;//��ʮλ�ƶ���λ
		}
		write_data('=');
		addflag=0;
	}
	
	
	
	else if(subflag)
	{
		
		write_com(0x80+0x4f);//�ڶ������ұ߿�ʼ
		write_com(0x04);//ÿ����һ���ַ���������һλ
		
	if(sum2>sum1)
	{
		sum2-=sum1;
		while(sum2!=0)//��sumÿһλ���ӵ�λ�������
		{
			write_data(0x30+sum2%10);//ת��Ϊasccii�����
			sum2/=10;//��ʮλ�ƶ���λ
		}
	}
	else if(sum2<sum1)
	{
		sum1-=sum2;
		while(sum1!=0)//��sumÿһλ���ӵ�λ�������
		{
			write_data(0x30+sum1%10);//ת��Ϊasccii�����
			sum1/=10;//��ʮλ�ƶ���λ
		}
			write_data('-');
	}
	else if(sum2==sum1)
	{
		write_data(0x30+0x00);
	}
	write_data('=');
	subflag=0;
	}
	
	
	//�˷�����
	else if(mulflag)//�˷�����
	{
		sum2*=sum1;
		write_com(0x80+0x4f);//�ڶ������ұ߿�ʼ
		write_com(0x04);//ÿ����һ���ַ���������һλ
		
		while(sum2!=0)//��sumÿһλ���ӵ�λ�������
		{
			write_data(0x30+sum2%10);//ת��Ϊasccii�����
			sum2/=10;//��ʮλ�ƶ���λ
		}
		write_data('=');
		mulflag=0;
	}
	
	
	
	//��������
	else if(divflag)
	{
		u8 a,c;
		u16 d,e,f;
		float b;
		a=(sum3/sum1)/1;//��������
		c=a;
		b=(sum3/sum1)-a;//С�����֣����Ǹ�����
		sum2=b*100;
		e=b*1000;//����1000ȡ��,���һλ��Ϊ�ж��Ƿ�Ҫ�����������룬ʵ�ʻ��Ǳ�����λС��
		d=e%10;//d��Ϊ�ж�λ
		if(d>4)
		{
			sum2+=1;
		}
		write_com(0x4f+0x80);
    write_com(0x04);
		while(sum2!=0)//��sumÿһλ���ӵ�λ�������
		{
			f++;
			write_data(0x30+sum2%10);//ת��Ϊasccii�����
			sum2/=10;//��ʮλ�ƶ���λ
		}
		if(f==1)//��������С�����ֵ�һλΪ�������£�����һ���㡣����0.09
		{
		 write_data(0x30+0x00);
			f=0;
		}
		write_data('.');
		
	  while(a!=0)//��sumÿһλ���ӵ�λ�������
		{
			write_data(0x30+a%10);//ת��Ϊasccii�����
			a/=10;//��ʮλ�ƶ���λ
		}
		if(c==0)
		{
			write_data(0x30+0x00);//�������������Ϊ0��С����ǰ�滹�и�0
		}
		write_data('=');
		divflag=0;
	}
	
}


void cal(void)
{
	matrixkeyscan();
	if(key_flag==1)
	{
		key_flag=0;
	switch(key_status2)
	{
		case 10:add();write_data(mat[key_status2]);
		break;
		
		case 11:sub();write_data(mat[key_status2]);
		break;
		
		case 12:mul();write_data(mat[key_status2]);
		break;
		case 13:div();write_data(mat[key_status2]);
		break;
		case 14:equal();
		break;
		default:data_process();
		break;
	}
}
}




