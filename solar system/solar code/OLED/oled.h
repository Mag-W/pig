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

void OLED_send_cmd(uint8_t o_command);//写命令
void OLED_send_data(uint8_t o_data);//写字数据
void Column_set(uint8_t column);
void OLED_Init(void);//初始化
void fill_picture(uint8_t fill_Data);
void OLED_Set_Pos(uint8_t x,uint8_t y);//坐标显示
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void); //点亮屏幕  
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size);//在指定位置显示一个字符,包括部分字符
//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n);

//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size);
//显示汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size2);
      	
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(uint8_t x0, uint8_t y0,uint8_t x1, uint8_t y1,uint8_t BMP[]);


void OLED_Refresh(void);//将128*8数组写入屏幕
void Draw_Point(uint8_t x, uint8_t y,uint8_t t);//画点函数
void GUI_Hline(uint8_t x,uint8_t y,uint8_t x0);//画水平直线
void GUI_Vline(uint8_t x,uint8_t y,uint8_t y0);//画垂直直线
void GUI_Axis();//画一个坐标轴
void GUI_Clear();//数组清零
	
#endif





