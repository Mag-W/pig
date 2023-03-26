#ifndef _ADC_H
#define _ADC_H

#include "public.h"

//ADS7830
#define ADC_Address_W 0x90//设备写入地址
#define ADC_Address_R 0x91//设备读地址

//ADC通道的控制字
#define ADC_CH0     0x04
#define ADC_CH1     0x44
#define ADC_CH2     0x14
#define ADC_CH3     0x54
#define ADC_CH4     0x24//测的电池电压


uint8_t ADS7830_GetADC_CHx(uint8_t ADC_CHx);
#endif

