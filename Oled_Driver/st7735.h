#ifndef __ST7735_H__
#define __ST7735_H__

#include "main.h"

//-------------------IC最大支持的分辨率-------------------
//#define TFT_IC_WIDTH_PIXEL (132)
//#define TFT_IC_HIGH_PIXEL  (162)
//#define TFT_IC_PIXEL  (TFT_IC_WIDTH_PIXEL*TFT_IC_HIGH_PIXEL)

void ST7735_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

void ST7735_Set_RGB444_Mode(void);
void ST7735_Set_RGB565_Mode(void);

void ST7735_Init(void);


#endif
