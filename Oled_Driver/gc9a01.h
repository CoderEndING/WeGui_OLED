#ifndef __GERNAL_TFT_IC_H__
#define __GERNAL_TFT_IC_H__

#include "main.h"

//-------------------IC最大支持的分辨率-------------------
#define TFT_IC_WIDTH_PIXEL (240)
#define TFT_IC_HIGH_PIXEL  (240)
#define TFT_IC_PIXEL  (TFT_IC_WIDTH_PIXEL*TFT_IC_HIGH_PIXEL)

void GC9A01_Set_Addr(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

void GC9A01_Set_RGB444_Mode(void);
void GC9A01_Set_RGB565_Mode(void);

void GC9A01_Init(void);

#endif
