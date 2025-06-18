#ifndef _STM32F103_WEGUI_6KEY_PORT_H_
#define _STM32F103_WEGUI_6KEY_PORT_H_

#include "stm32f10x.h"
#include "lcd_WeGui_driver.h"










//-------------------------------------按键配置-------------------------------------


//#define WeGui_KeyBack_GPIOx                 GPIOC
//#define WeGui_KeyBack_GPIO_Pin_x            GPIO_Pin_15
//#define WeGui_KeyBack_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOC
//#define WeGui_KeyBack_IO_Init()                                        \
//do                                                                  \
//{                                                                   \
//    GPIO_InitTypeDef GPIO_InitStruct;                               \
//    GPIO_InitStruct.GPIO_Pin   = WeGui_KeyBack_GPIO_Pin_x;             \
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
//	  RCC_APB2PeriphClockCmd(WeGui_KeyBack_RCC_APB2Periph_GPIOx,ENABLE); \
//    GPIO_Init(WeGui_KeyBack_GPIOx, &GPIO_InitStruct);                  \
//}while(0)

//#define WeGui_KeyOk_GPIOx                 GPIOA
//#define WeGui_KeyOk_GPIO_Pin_x            GPIO_Pin_0
//#define WeGui_KeyOk_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOA
//#define WeGui_KeyOk_IO_Init()                                        \
//do                                                                  \
//{                                                                   \
//    GPIO_InitTypeDef GPIO_InitStruct;                               \
//    GPIO_InitStruct.GPIO_Pin   = WeGui_KeyOk_GPIO_Pin_x;             \
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
//    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
//	  RCC_APB2PeriphClockCmd(WeGui_KeyOk_RCC_APB2Periph_GPIOx,ENABLE); \
//    GPIO_Init(WeGui_KeyOk_GPIOx, &GPIO_InitStruct);                  \
//}while(0)

#define WeGui_KeyRight_GPIOx                 GPIOB
#define WeGui_KeyRight_GPIO_Pin_x            GPIO_Pin_12
#define WeGui_KeyRight_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WeGui_KeyRight_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = WeGui_KeyRight_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(WeGui_KeyRight_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(WeGui_KeyRight_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define WeGui_KeyUp_GPIOx                 GPIOB
#define WeGui_KeyUp_GPIO_Pin_x            GPIO_Pin_13
#define WeGui_KeyUp_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WeGui_KeyUp_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = WeGui_KeyUp_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(WeGui_KeyUp_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(WeGui_KeyUp_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define WeGui_KeyDown_GPIOx                 GPIOB
#define WeGui_KeyDown_GPIO_Pin_x            GPIO_Pin_14
#define WeGui_KeyDown_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WeGui_KeyDown_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = WeGui_KeyDown_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(WeGui_KeyDown_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(WeGui_KeyDown_GPIOx, &GPIO_InitStruct);                  \
}while(0)

#define WeGui_KeyLeft_GPIOx                 GPIOB
#define WeGui_KeyLeft_GPIO_Pin_x            GPIO_Pin_15
#define WeGui_KeyLeft_RCC_APB2Periph_GPIOx  RCC_APB2Periph_GPIOB
#define WeGui_KeyLeft_IO_Init()                                        \
do                                                                  \
{                                                                   \
    GPIO_InitTypeDef GPIO_InitStruct;                               \
    GPIO_InitStruct.GPIO_Pin   = WeGui_KeyLeft_GPIO_Pin_x;             \
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;                   \
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;                     \
	  RCC_APB2PeriphClockCmd(WeGui_KeyLeft_RCC_APB2Periph_GPIOx,ENABLE); \
    GPIO_Init(WeGui_KeyLeft_GPIOx, &GPIO_InitStruct);                  \
}while(0)





//开发板正向按键
/*---------------------------
	*  ---默认按键接口---
	*  |OK   | A0  |确定|
	*  |BACK | C15 |返回|
	*  |UP   | B13 | 上 |
	*  |DOWN | B14 | 下 |
	*  |LEFT | B15 | 左 |
	*  |RIGHT| B12 | 右 |
----------------------------*/
//#define Bool_WKeyBack_is_Pressed()  (GPIO_ReadInputDataBit(WeGui_KeyBack_GPIOx, WeGui_KeyBack_GPIO_Pin_x) == RESET)
//#define Bool_WKeyOk_is_Pressed()    (GPIO_ReadInputDataBit(WeGui_KeyOk_GPIOx, WeGui_KeyOk_GPIO_Pin_x) == RESET)
#define Bool_WkeyRight_is_Pressed() (GPIO_ReadInputDataBit(WeGui_KeyRight_GPIOx, WeGui_KeyRight_GPIO_Pin_x) == RESET)
#define Bool_WKeyUp_is_Pressed()    (GPIO_ReadInputDataBit(WeGui_KeyUp_GPIOx, WeGui_KeyUp_GPIO_Pin_x) == RESET)
#define Bool_WKeyDown_is_Pressed()  (GPIO_ReadInputDataBit(WeGui_KeyDown_GPIOx, WeGui_KeyDown_GPIO_Pin_x) == RESET)
#define Bool_WkeyLeft_is_Pressed()  (GPIO_ReadInputDataBit(WeGui_KeyLeft_GPIOx, WeGui_KeyLeft_GPIO_Pin_x) == RESET)





//-------------------------------------声明-------------------------------------
void WeGui_4key_port_Init(void);
void WeGui_Interface_stick(uint16_t ms);


#endif
