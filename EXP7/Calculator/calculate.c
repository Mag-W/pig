#include "calculate.h"

u8 code  mat[]={'0','1','2','3','4','5','6','7','8','9','+','-','*','/','='};

u16 sum1,sum2;
float sum3 ; //用于除法
u8 addflag,subflag,mulflag,divflag;
u8 keyflag; //	在keyvaluechuli()函数中控制
u8 flag ;// 控制乘中的sum1;


void data_process()  //  0~9
{
   if(key_status2==15)//key15作为清零键
   { 
    write_com(0x01);
	 sum1=sum2=0;
	 addflag=0;
	 subflag=0;
	 mulflag=0;
	 divflag=0;	 
   }
   if(key_status2<10)//即输入0-9数字
   {
     if(flag==1)   //flag在乘中控制使按下一个数据清除sum1
	 {
	  sum1=0;
	  flag=0;
	 }
	  sum1=sum1*10+key_status2;
	  write_data(mat[key_status2]);//把新输入的数显示
   }
}




void add(void)
{
  addflag++;//加法标志位加1
  subflag=mulflag=divflag=0;//其他标志位清零
  sum2=sum1; //将新输入的sum1送给sum2保存
  sum1=0;   //置零
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



void equal(void)//计算最后的结果
{
	if(addflag)
	{
		sum2+=sum1;
		write_com(0x80+0x4f);//第二行最右边开始
		write_com(0x04);//每输入一个字符，就左移一位
		
		while(sum2!=0)//将sum每一位都从低位依次输出
		{
			write_data(0x30+sum2%10);//转化为asccii码输出
			sum2/=10;//将十位移动个位
		}
		write_data('=');
		addflag=0;
	}
	
	
	
	else if(subflag)
	{
		
		write_com(0x80+0x4f);//第二行最右边开始
		write_com(0x04);//每输入一个字符，就左移一位
		
	if(sum2>sum1)
	{
		sum2-=sum1;
		while(sum2!=0)//将sum每一位都从低位依次输出
		{
			write_data(0x30+sum2%10);//转化为asccii码输出
			sum2/=10;//将十位移动个位
		}
	}
	else if(sum2<sum1)
	{
		sum1-=sum2;
		while(sum1!=0)//将sum每一位都从低位依次输出
		{
			write_data(0x30+sum1%10);//转化为asccii码输出
			sum1/=10;//将十位移动个位
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
	
	
	//乘法部分
	else if(mulflag)//乘法部分
	{
		sum2*=sum1;
		write_com(0x80+0x4f);//第二行最右边开始
		write_com(0x04);//每输入一个字符，就左移一位
		
		while(sum2!=0)//将sum每一位都从低位依次输出
		{
			write_data(0x30+sum2%10);//转化为asccii码输出
			sum2/=10;//将十位移动个位
		}
		write_data('=');
		mulflag=0;
	}
	
	
	
	//除法部分
	else if(divflag)
	{
		u8 a,c;
		u16 d,e,f;
		float b;
		a=(sum3/sum1)/1;//整数部分
		c=a;
		b=(sum3/sum1)-a;//小数部分，还是浮点数
		sum2=b*100;
		e=b*1000;//乘上1000取整,最后一位作为判断是否要进行四舍五入，实际还是保留两位小数
		d=e%10;//d作为判断位
		if(d>4)
		{
			sum2+=1;
		}
		write_com(0x4f+0x80);
    write_com(0x04);
		while(sum2!=0)//将sum每一位都从低位依次输出
		{
			f++;
			write_data(0x30+sum2%10);//转化为asccii码输出
			sum2/=10;//将十位移动个位
		}
		if(f==1)//这里是在小数部分第一位为零的情况下，补上一个零。比如0.09
		{
		 write_data(0x30+0x00);
			f=0;
		}
		write_data('.');
		
	  while(a!=0)//将sum每一位都从低位依次输出
		{
			write_data(0x30+a%10);//转化为asccii码输出
			a/=10;//将十位移动个位
		}
		if(c==0)
		{
			write_data(0x30+0x00);//如果商整数部分为0，小数点前面还有个0
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




