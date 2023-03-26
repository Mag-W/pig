#include "oled.h"
#include "oled_font.h"

uint8_t xdata OLED_Gram[8][128];
const uint8_t code OLED_init_cmd[25]=
{
  /*0xae,0X00,0X10,0x40,0X81,0XCF,0xff,0xa1,0xa4,
  0xA6,0xc8,0xa8,0x3F,0xd5,0x80,0xd3,0x00,0XDA,0X12,
  0x8d,0x14,0xdb,0x40,0X20,0X02,0xd9,0xf1,0xAF*/
       0xAE,//�ر���ʾ
       0xD5,//����ʱ�ӷ�Ƶ����,��Ƶ��
       0x80,  //[3:0],��Ƶ����;[7:4],��Ƶ��
       0xA8,//��������·��
       0X3F,//Ĭ��0X3F(1/64)
       0xD3,//������ʾƫ��
       0X00,//Ĭ��Ϊ0
       0x40,//������ʾ��ʼ�� [5:0],����.                              
       0x8D,//��ɱ�����
       0x14,//bit2������/�ر�
       0x20,//�����ڴ��ַģʽ
       0x02,//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
       0xA1,//���ض�������,bit0:0,0->0;1,0->127;
       0xC8,//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
       0xDA,//����COMӲ����������
       0x12,//[5:4]����            
       0x81,//�Աȶ�����
       0xEF,//1~255;Ĭ��0X7F (��������,Խ��Խ��)
       0xD9,//����Ԥ�������
       0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
       0xDB,//����VCOMH ��ѹ����
       0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
       0xA4,//ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
       0xA6,//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ        
       0xAF,//������ʾ     
};


void OLED_send_cmd(uint8_t o_command)//д����
{
	  I2C_Start();
    write_byte(0x78);//OLED��ַ
    read_ACK();
    write_byte(0x00);//�Ĵ�����ַ
    read_ACK();
    write_byte(o_command);
    read_ACK();
    I2C_Stop();
}

void OLED_send_data(uint8_t o_data)//д������
{
  	I2C_Start();
	  write_byte(0x78);//OLED��ַ
    read_ACK();
    write_byte(0x40);//�Ĵ�����ַ
    read_ACK();
    write_byte(o_data);
    read_ACK();
    I2C_Stop();
}

void Column_set(uint8_t column)
{
	OLED_send_cmd(0x10|(column>>4));    //�����е�ַ��λ
	OLED_send_cmd(0x00|(column&0x0f));  //�����е�ַ��λ   
}


void OLED_Init(void)
{
	uint8_t i;
	I2C_Init();		//��ʼ��IIC
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


//��������
//x��0-127��y��0-7
void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 	
	OLED_send_cmd(0xb0+y);
	OLED_send_cmd(((x&0xf0)>>4)|0x10);
	OLED_send_cmd(x&0x0f); 
}   	  

//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_send_cmd(0X8D);  //SET DCDC����
	OLED_send_cmd(0X14);  //DCDC ON
	OLED_send_cmd(0XAF);  //DISPLAY ON
}

//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_send_cmd(0X8D);  //SET DCDC����
	OLED_send_cmd(0X10);  //DCDC OFF
	OLED_send_cmd(0XAE);  //DISPLAY OFF
}		   

//��������,������,������Ļ�Ǻ�ɫ��  
void OLED_Clear(void)  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_send_cmd (0xb0+i);    //����ҳ��ַ��0~7��
		OLED_send_cmd (0x00);      //������ʾλ�á��е͵�ַ
		OLED_send_cmd (0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_send_data(0x00); 
	} //������ʾ
}

 
void OLED_On(void) //������Ļ  
{  
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_send_cmd (0xb0+i);    //����ҳ��ַ��0~7��
		OLED_send_cmd (0x00);      //������ʾλ�á��е͵�ַ
		OLED_send_cmd (0x10);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_send_data(0xff); 
	} //������ʾ
}



//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~7
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size)
{      	
	  uint8_t c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
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

//m^n����
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
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

//��ʾһ���ַ��Ŵ�
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

//��ʾ����
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


/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
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
		OLED_send_cmd(0xb0+j);//����ҳ��ַλ0-7
		OLED_send_cmd(0x00);//�еĵ͵�ַ
		OLED_send_cmd(0x10);//�еĸߵ�ַ
		for(i=0;i<128;i++)OLED_send_data(OLED_Gram[j][i]);
	}
}



/*���㺯����x 0-127,y 0-7,t 1Ϊ��� 0Ϊ���*/
void Draw_Point(uint8_t x, uint8_t y,uint8_t t)
{
	uint8_t pos,bx,temp;
	if(x>127||y>63)return;
	pos=y/8;//pos����0-7֮��,���Ǵ��ڵڼ�ҳ
	bx=y%8;//bxҲ����0-7֮�䣬���ڸ�ҳ�ĵڼ���λ��
	temp=1<<bx;//��1����bxλ��ŵ�temp��,��ʱ��temp������Ҫ���ĵط���Ϊ1
//	OLED_Set_Pos(x,pos);
//	OLED_send_data(temp); 
	if(t)OLED_Gram[pos][x]|=temp;//��ԭ����ȡ�򣬱���ԭ�е�1
	else OLED_Gram[pos][x]&=~temp;
}

/*��ˮƽֱ�ߣ�(x,y)��ֱ����㣬x0�ǽ���λ��*/
void GUI_Hline(uint8_t x,uint8_t y,uint8_t x0)
{
	uint8_t i;
	for(i=x;i<x0;i++)Draw_Point(i,y,1);
}

/*����ֱֱ�ߣ�(x,y)��ֱ����㣬y0�ǽ���λ��*/
void GUI_Vline(uint8_t x,uint8_t y,uint8_t y0)
{
	uint8_t j;
	for(j=y;j<y0;j++)Draw_Point(x,j,1);
}

/*��һ������*/
void GUI_Axis()
{
	GUI_Hline(2,60,100);
	GUI_Vline(2,2,60);
}

/*��������*/
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



	