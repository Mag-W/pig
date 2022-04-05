/* Created by:               Mag.W
** Created date:             2022/4/03
** The last updated date:    2022/4/05
** Version:                  3.0
*/
#include "public.h"
#include "1602.h"
#include "key.h"
#include "ad.h"
#include "string.h"
#include "calculate.h"


void main()
{	
	u16 adc_value=0;
	
	
	lcd_init();//LCD1602初始化
//	lcd1602_show_string(0,0,"Hello World!");//第一行显示
//	lcd1602_show_string(0,1,"0123456789");//第二行显示
	  //write_data(0x4f+0x80); //从第二行从右向左写数据
		//write_com(0x04);
	while(1)
	{
  		key_scan();
   		cal();
	   	adc_value=xpt2046_read_adc_value(0xA4);//测量光敏电阻
		
		switch(key_status1)
		{
			case 1:
				if(key_flag1==1)
				{
				key_flag1=0;
				lcd_clear();
				}
				AD_Display(adc_value);
				
			break;
			case 2:if(key_flag1==1)
			{
				key_flag1=0;
				lcd_clear();
			}
				cal();
			break;
			case 3:lcd_clear();
			break;
			default:break;
		}
	}	
}


