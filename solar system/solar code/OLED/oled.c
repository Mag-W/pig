#include "oled.h"
#include "oled_font.h"

uint8_t xdata OLED_Gram[8][128];
const uint8_t code OLED_init_cmd[25]=
{
  /*0xae,0X00,0X10,0x40,0X81,0XCF,0xff,0xa1,0xa4,
  0xA6,0xc8,0xa8,0x3F,0xd5,0x80,0xd3,0x00,0XDA,0X12,
  0x8d,0x14,0xdb,0x40,0X20,0X02,0xd9,0xf1,0xAF*/
       0xAE,//关闭显示
       0xD5,//设置时钟分频因子,震荡频率
       0x80,  //[3:0],分频因子;[7:4],震荡频率
       0xA8,//设置驱动路数
       0X3F,//默认0X3F(1/64)
       0xD3,//设置显示偏移
       0X00,//默认为0
       0x40,//设置显示开始行 [5:0],行数.                              
       0x8D,//电荷泵设置
       0x14,//bit2，开启/关闭
       0x20,//设置内存地址模式
       0x02,//[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
       0xA1,//段重定义设置,bit0:0,0->0;1,0->127;
       0xC8,//设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
       0xDA,//设置COM硬件引脚配置
       0x12,//[5:4]配置            
       0x81,//对比度设置
       0xEF,//1~255;默认0X7F (亮度设置,越大越亮)
       0xD9,//设置预充电周期
       0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
       0xDB,//设置VCOMH 电压倍率
       0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
       0xA4,//全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
       0xA6,//设置显示方式;bit0:1,反相显示;0,正常显示        
       0xAF,//开启显示     
};


void OLED_send_cmd(uint8_t o_command)//写命令
{
	  I2C_Start();
    write_byte(0x78);//OLED地址
    read_ACK();
    write_byte(0x00);//寄存器地址
    read_ACK();
    write_byte(o_command);
    read_ACK();
    I2C_Stop();
}

void OLED_send_data(uint8_t o_data)//写字数据
{
  	I2C_Start();
	  write_byte(0x78);//OLED地址
    read_ACK();
    write_byte(0x40);//寄存器地址
    read_ACK();
    write_byte(o_data);
    read_ACK();
    I2C_Stop();
}

void Column_set(uint8_t column)
{
	OLED_send_cmd(0x10|(column>>4));    //设置列地址高位
	OLED_send_cmd(0x00|(column&0x0f));  //设置列地址低位   
}


void OLED_Init(void)
{
	uint8_t i;
	I2C_Init();		//初始化IIC
	for(i=0;i<25;i++)
	{
		OLED_send_cmd(OLED_init_cmd[i]);
	}
}


void fill_picture(uint8_t fill_Data)
{
	uint8_t m,n;
	for(m=0;m<8;m++)
	{
		OLED_send_cmd(0xb0+m);		//page0-page1
		OLED_send_cmd(0x00);		//low column start address
		OLED_send_cmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_send_data(fill_Data);
			}
	}
}


//坐标设置
//x在0-127，y在0-7
void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 	
	OLED_send_cmd(0xb0+y);
	OLED_send_cmd(((x&0xf0)>>4)|0x10);
	OLED_send_cmd(x&0x0f); 
}   	  

//开启OLED显示
void OLED_Display_On(void)
{
	OLED_send_cmd(0X8D);  //SET DCDC命令
	OLED_send_cmd(0X14);  //DCDC ON
	OLED_send_cmd(0XAF);  //DISPLAY ON
}

//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_send_cmd(0X8D);  //SET DCDC命令
	OLED_send_cmd(0X10);  //DCDC OFF
	OLED_send_cmd(0XAE);  //DISPLAY OFF
}		   

//清屏函数,清完屏,整个屏幕是黑色的  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_send_cmd (0xb0+i);    //设置页地址（0~7）
		OLED_send_cmd (0x00);      //设置显示位置—列低地址
		OLED_send_cmd (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_send_data(0x00); 
	} //更新显示
}

 
void OLED_On(void) //点亮屏幕  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_send_cmd (0xb0+i);    //设置页地址（0~7）
		OLED_send_cmd (0x00);      //设置显示位置—列低地址
		OLED_send_cmd (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_send_data(0xff); 
	} //更新显示
}



//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~7
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	  uint8_t c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_send_data(F8X16[c*16+i]);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_send_data(F8X16[c*16+i+8]);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_send_data(F6x8[c][i]);
			}
}

//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size)
{
	uint8_t j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//显示汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_send_data(Hzk[2*no][t]);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_send_data(Hzk[2*no+1][t]);
				adder+=1;
      }					
}


/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[])
{ 	
 uint16_t j=0;
 uint8_t x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_send_data(BMP[j++]);	    	
	    }
	}
} 


void OLED_Refresh(void)
{
	uint8_t i,j;
	for(j=0;j<8;j++)
	{
		OLED_send_cmd(0xb0+j);//设置页地址位0-7
		OLED_send_cmd(0x00);//列的低地址
		OLED_send_cmd(0x10);//列的高地址
		for(i=0;i<128;i++)OLED_send_data(OLED_Gram[j][i]);
	}
}



/*画点函数，x 0-127,y 0-7,t 1为填充 0为清空*/
void Draw_Point(uint8_t x, uint8_t y,uint8_t t)
{
	uint8_t pos,bx,temp;
	if(x>127||y>63)return;
	pos=y/8;//pos处于0-7之间,就是处在第几页
	bx=y%8;//bx也处于0-7之间，处在该页的第几个位置
	temp=1<<bx;//把1左移bx位后放到temp中,这时的temp可以让要亮的地方置为1
//	OLED_Set_Pos(x,pos);
//	OLED_send_data(temp); 
	if(t)OLED_Gram[pos][x]|=temp;//和原数组取或，保留原有的1
	else OLED_Gram[pos][x]&=~temp;
}

/*画水平直线，(x,y)是直线起点，x0是结束位置*/
void GUI_Hline(uint8_t x,uint8_t y,uint8_t x0)
{
	uint8_t i;
	for(i=x;i<x0;i++)Draw_Point(i,y,1);
}

/*画垂直直线，(x,y)是直线起点，y0是结束位置*/
void GUI_Vline(uint8_t x,uint8_t y,uint8_t y0)
{
	uint8_t j;
	for(j=y;j<y0;j++)Draw_Point(x,j,1);
}

/*画一个坐标*/
void GUI_Axis()
{
	GUI_Hline(2,60,100);
	GUI_Vline(2,2,60);
}

/*数组清零*/
void GUI_Clear()
{
	uint8_t i,j;
	for(j=0;j<8;j++)
	{
		for(i=0;i<128;i++)
		{
			OLED_Gram[j][i]=0;
		}
	}
}



	