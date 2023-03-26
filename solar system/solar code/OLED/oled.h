#ifndef _OLED_H
#define _OLED_H


#include "i2c.h"

sbit LED_SCL = P1^0;
sbit LED_SDA = P1^1;


#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	

extern uint8_t xdata OLED_Gram[8][128];

void OLED_send_cmd(uint8_t o_command);//д����
void OLED_send_data(uint8_t o_data);//д������
void Column_set(uint8_t column);
void OLED_Init(void);//��ʼ��
void fill_picture(uint8_t fill_Data);
void OLED_Set_Pos(uint8_t x,uint8_t y);//������ʾ
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void); //������Ļ  
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);//��ָ��λ����ʾһ���ַ�,���������ַ�
//m^n����
uint32_t oled_pow(uint8_t m,uint8_t n);

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);
//��ʾ����
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);
      	
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]);


void OLED_Refresh(void);//��128*8����д����Ļ
void Draw_Point(uint8_t x, uint8_t y,uint8_t t);//���㺯��
void GUI_Hline(uint8_t x,uint8_t y,uint8_t x0);//��ˮƽֱ��
void GUI_Vline(uint8_t x,uint8_t y,uint8_t y0);//����ֱֱ��
void GUI_Axis();//��һ��������
void GUI_Clear();//��������
	
#endif





