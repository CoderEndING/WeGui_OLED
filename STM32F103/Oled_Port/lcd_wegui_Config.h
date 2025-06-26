#ifndef LCD_Wegui_CONFIG_H
#define LCD_Wegui_CONFIG_H


/*--------------------------------------------------------------
  * Wegui : V0.3beta
  * Author: KOUFU
	* https://space.bilibili.com/526926544
	* https://github.com/KOUFU-DIY/Wegui_OLED
----------------------------------------------------------------*/
/*--------------------------------------------------------------
  * 版本更新 : V0.3beta
	* 1.修复多余2page的ram占用
	* 2.修复缺少ssd1309驱动文件的问题
  * 3.1.升级配套WeGui上位机,对应文件stm32f103_wegui_uart_port.c
	* 3.2.增加uart电脑"录屏串流"功能, 使用上位机进行串流(串流时调试信息FPS不准确)
	* 3.3.上位机支持模拟按键操作
----------------------------------------------------------------*/

/*--------------------------------------------------------------
	* 暂不支持使用ARMV6编译,请使用ARMV5编译器(默认)
	* 若keil版本过高,请自行安装v5版本编译器
	* 本程序使用了大量的"UTF8"支持多国语言的编码
	* 需要进行两步设置
	* 1.Edit->Configuration->Encoding->"Encod in UTF8"
	* 2.Project -> Oprions for Target-> C/C++ -> 
	* Misc Contiols -> 填入"--locale=english"
----------------------------------------------------------------*/
//提示: 
//IIC相关功能暂不支持使用ARMV6编译,请使用ARMV5编译器!!
//该芯片IIC存在"缺陷",其怪点暂未解决,暂未适配其DMA驱动方式, 推荐使用软件IIC方式!!
//IIC硬件在一次通讯失败后,将拖慢系统运行,暂未解决, 推荐使用软件IIC方式!!
//软件IIC默认使用适中的延迟速率,需要更快的刷新速度,需要到对应port文件里修改, 查找I2C_SCL_Rise_Delay等并进行修改延迟值
//使用模拟IIC可精确控制上升和下降时间,调整合适的延迟时间,刷新率可以比硬件IIC更快

//该工程支持"全屏刷新"和"动态刷新"两种刷屏方式(DMA方式强制使用全屏刷新)

//"动态刷新"以牺牲一些全屏刷新速度换取普通刷新的速度, 但同时在屏幕静止时, cpu占用极低
//刷新方式在下方通过宏定义调整切换

//默认开启右下角调试状态显示,若要关闭,查找注释掉调用的Wegui_update_info(fps_time_count);
//字库及其他资源在lcd_res,可自行使用配套工具修改裁剪多国语言字库, 随后会更新视频教程

/*------------------------------------------------------------------------------------
	* ----默认驱动接口----        ---默认按键接口---          外接ADC电位器接口 A1
	* |--SPI--|  |--IIC--|       |OK   | A0  |确定|         (用于DEMO外部数据演示)
	* |BL   B0|  |RES  A6|       |BACK | C15 |返回|          
	* |CS   A6|  |SDA B11|       |UP   | B13 | 上 |         板载闪烁LED  C13
	* |DC  B11|  |SCL B10|       |DOWN | B14 | 下 |    
	* |RES B10|  |3V3 3V3|       |LEFT | B15 | 左 |    
	* |SDA  A7|  |GND GND|       |RIGHT| B12 | 右 |    
	* |SCL  A5|                                       
	* |3V3 3V3|  
  * |GND GND|
-------------------------------------------------------------------------------------*/






//-------------------------1.选择一个屏幕通讯接口-----------------------------

//#define LCD_USE_SOFT_3SPI  //软件三线SPI驱动   对应文件stm32f103_lcd_soft_3spi_port.c
//#define LCD_USE_SOFT_4SPI  //软件四线SPI驱动   对应文件stm32f103_lcd_soft_4spi_port.c
//#define LCD_USE_HARD_4SPI  //硬件四线SPI驱动   对应文件stm32f103_lcd_hard_4spi_port.c
//#define LCD_USE_DMA_4SPI   //DMA四线SPI驱动   对应文件stm32f103_lcd_dma_4spi_port.c(暂不支持动态刷新)
#define LCD_USE_SOFT_IIC   //软件IIC驱动(推荐) 对应文件stm32f103_lcd_soft_iic_port.c 
//#define LCD_USE_HARD_IIC   //硬件IIC驱动(不推荐) 对应文件stm32f103_lcd_hard_iic_port.c (不推荐使用,应答等存在问题暂未解决)





//---------------------------2.1设定屏幕IIC地址--------------------------------

#if defined(LCD_USE_HARD_IIC) || defined(LCD_USE_SOFT_IIC) || defined(LCD_USE_DMA_IIC)
	#define OLED_IIC_7ADDR 0x3C //7位0x3C => 8位0x78 (大部分默认)
	//#define OLED_IIC_7ADDR 0x3D //7位0x3D => 8位0x7A
	 
#endif 

//-------------------------2.2设定硬件SPI时钟速率-------------------------------

#if defined(LCD_USE_HARD_4SPI) || defined(LCD_USE_DMA_4SPI)
//STM32F103手册指定SPI最高设置18MHz 但也支持超频
#define RCC_HCLK_Divx            RCC_HCLK_Div2 //HCLK时钟分频1,2,4,8,16
#define SPI_BaudRatePrescaler_x  SPI_BaudRatePrescaler_8 //SPI分频2,4,8,16,32,64,128,256
#endif


//----------------------------3.选择刷屏方式--------------------------------
//#define LCD_USE_FULL_REFRESH    //全屏刷新
#define LCD_USE_DYNAMIC_REFRESH //动态刷新(建议使用)


//----------------------------4.设定屏幕分辨率--------------------------------
#define SCREEN_WIDTH 128  //建议取8或2的倍数
#define SCREEN_HIGH  64  //建议取8或2的倍数


//-----------------------5.设定屏幕区域显示偏移设置--------------------------
//oled屏幕优先修改驱动初始化
#define SCREEN_X_OFFSET     0 //x左右方向偏移像素
#define SCREEN_Y_OFFSET     0 //y上下方向偏移像素


//-----------------------------6.选择屏幕IC---------------------------------
#define _SH1106    (0)//普通点阵OLED
#define _SH1108    (1)//普通点阵OLED
#define _SH1107    (2)//普通点阵OLED
#define _SH1115    (3)//普通点阵OLED
#define _SSD1306   (4)//普通点阵OLED (最常用)
#define _SSD1309   (5)//普通点阵OLED 
#define _SSD1312   (6)//普通点阵OLED
#define _SSD1315   (7)//普通点阵OLED
#define _SSD1327   (8)//灰度OLED
#define _ST7735    (9)//TFT彩屏 RGB565
#define _ST7789VW (10)//TFT彩屏 RGB565
#define _ST7796S  (11)//TFT彩屏 RGB565
#define _GC9A01   (12)//TFT彩屏 RGB565 (未完善)
//#define _ILI9488  (13)//TFT彩屏 RGB111 RGB888 暂不支持

#define LCD_IC _SSD1306 //选择一个屏幕IC型号


//----------------------------7.1设定彩屏---------------------------------
//仅"TFT彩屏"需要设置
#define LCD_DRAW_COLOUR  RGB565_White //画笔色
#define LCD_CLEAR_COLOUR RGB565_Black //背景色

//---------------------------7.2设定灰度屏--------------------------------
//仅"灰度OLED屏"需要设置

//1.选择一个灰度屏扫描方向[需要与初始化(A0指令)匹配]
#define GRAY_DRIVER_0DEG  //方向1
//#define GRAY_DRIVER_90DEG //方向2

//2.设置画笔灰度亮度[1:15]
#define GRAY_COLOUR  15 //画笔灰度(亮度)


//--------------------------6.选择一个GUI菜单交互方式-----------------------------
//#define Wegui_USE_NONE_PORT //无交互
//#define Wegui_USE_6KEY_PORT //6按键交互模式 "上","下","左","右","OK","BACK"
#define Wegui_USE_4KEY_PORT //4按键交互模式 "上","下","左","右"
//#define Wegui_USE_2KEY_PORT //(暂未适配)2按键交互模式 "BACK","OK"
//#define Wegui_USE_EC_PORT //(暂未适配)旋转编码器

//--------------------------7.启用UART(上位机功能)-----------------------------
//#define Wegui_UART_OFF //关闭
#define Wegui_UART_ON //启用






  
 

//------------编译-----------
#define GRAM_YPAGE_NUM ((SCREEN_HIGH+7)/8)


#if (LCD_IC == _SH1106)
	#include "sh1106.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SH1106_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SH1106_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SH1106_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SH1106_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{SH1106_Set_Contrast(x);}while(0)
#elif (LCD_IC == _SH1108)
	#include "sh1108.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SH1108_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SH1108_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SH1108_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SH1108_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{SH1108_Set_Contrast(x);}while(0)
#elif (LCD_IC == _SH1107)
	#include "SH1107.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SH1107_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SH1107_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SH1107_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SH1107_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0)
#elif (LCD_IC == _SH1115)
	#include "sh1115.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SH1115_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SH1115_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SH1115_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SH1115_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{SH1115_The_Contrast_Control_Mode_Set(x);}while(0)
#elif (LCD_IC == _SSD1306)
	#include "ssd1306.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SSD1306_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SSD1306_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SSD1306_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SSD1306_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0)
#elif (LCD_IC == _SSD1309)
	#include "ssd1309.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SSD1309_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SSD1309_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SSD1309_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SSD1309_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0)
#elif (LCD_IC == _SSD1312)
	#include "ssd1312.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SSD1312_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SSD1312_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SSD1312_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SSD1312_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0)
#elif (LCD_IC == _SSD1315)
	#include "ssd1315.h"
	#define LCD_USE_NORMAL_OLED
	#define LCD_IC_Init() do{SSD1315_Init();}while(0)
	#define LCD_Set_Addr_x(x) do{SSD1315_Set_Address_x(x+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_ypage(page) do{SSD1315_Set_Address_ypage(page+SCREEN_Y_OFFSET/8);}while(0)
	#define LCD_Set_Addr(x,page) do{SSD1315_Set_Address_x_ypage((x+SCREEN_X_OFFSET),(page+SCREEN_Y_OFFSET/8));}while(0)
	#define LCD_Set_Bright(x) do{SSD1315_Set_Contrast_Control(x);}while(0)

#elif (LCD_IC == _SSD1327)
	#include "ssd1327.h"
	#define LCD_USE_GRAY_OLED
	#define LCD_IC_Init() do{SSD1327_Init();}while(0)
	#define LCD_Set_Addr_x(x0,x1) do{SSD1327_Set_Addr_x(x0+SCREEN_X_OFFSET,x1+SCREEN_X_OFFSET);}while(0)
	#define LCD_Set_Addr_y(y0,y1) do{SSD1327_Set_Addr_y(y0+SCREEN_Y_OFFSET,y1+SCREEN_Y_OFFSET);}while(0)
	#define LCD_Set_Addr(x0,y0,x1,y1) do{SSD1327_Set_Addr(x0+SCREEN_X_OFFSET,y0+SCREEN_Y_OFFSET,x1+SCREEN_X_OFFSET,y1+SCREEN_Y_OFFSET);}while(0)
	#define LCD_Set_Bright(x) do{/*SSD1327_Set_Contrast_Control(x);*/}while(0)
#elif (LCD_IC == _ST7735)
	#include "st7735.h"
	#include "TFT_Color.h"
	#define LCD_USE_RGB565
	#define LCD_IC_Init() do{ST7735_Init();}while(0)
	#define LCD_Set_Addr(x0,y0,x1,y1) do{ST7735_Set_Addr(x0+SCREEN_X_OFFSET,y0+SCREEN_Y_OFFSET,x1+SCREEN_X_OFFSET,y1+SCREEN_Y_OFFSET);}while(0)
	#define LCD_Set_Bright(x) do{}while(0)
#elif (LCD_IC == _ST7789VW)
	#include "st7789vw.h"
	#include "TFT_Color.h"
	#define LCD_USE_RGB565
	#define LCD_IC_Init() do{ST7789VW_Init();}while(0)
	#define LCD_Set_Addr(x0,y0,x1,y1) do{ST7789VW_Set_Addr(x0+SCREEN_X_OFFSET,y0+SCREEN_Y_OFFSET,x1+SCREEN_X_OFFSET,y1+SCREEN_Y_OFFSET);}while(0)
	#define LCD_Set_Bright(x) do{}while(0)
#elif (LCD_IC == _ST7796S)
	#include "st7796s.h"
	#include "TFT_Color.h"
	#define LCD_USE_RGB565
	#define LCD_IC_Init() do{ST7796S_Init();}while(0)
	#define LCD_Set_Addr(x0,y0,x1,y1) do{ST7796S_Set_Addr(x0+SCREEN_X_OFFSET,y0+SCREEN_Y_OFFSET,x1+SCREEN_X_OFFSET,y1+SCREEN_Y_OFFSET);}while(0)
	#define LCD_Set_Bright(x) do{}while(0)
#elif (LCD_IC == _GC9A01)
	#include "gc9a01.h"
	#include "TFT_Color.h"
	#define LCD_USE_RGB565
	#define LCD_IC_Init() do{GC9A01_Init();}while(0)
	#define LCD_Set_Addr(x0,y0,x1,y1) do{GC9A01_Set_Addr(x0+SCREEN_X_OFFSET,y0+SCREEN_Y_OFFSET,x1+SCREEN_X_OFFSET,y1+SCREEN_Y_OFFSET);}while(0)
	#define LCD_Set_Bright(x) do{}while(0)
#else
	#warning("No screen ic init!")
#endif


#if defined LCD_USE_SOFT_3SPI    //软件三线SPI 
	#include "stm32f103_lcd_soft_3spi_port.h"
#elif defined LCD_USE_SOFT_4SPI //软件四线SPI 
	#include "stm32f103_lcd_soft_4spi_port.h"
#elif defined LCD_USE_HARD_4SPI //硬件四线SPI 
	#include "stm32f103_lcd_hard_4spi_port.h"
#elif defined LCD_USE_DMA_4SPI //DMA四线SPI 
	#include "stm32f103_lcd_dma_4spi_port.h"
#elif defined LCD_USE_SOFT_IIC  //软件IIC   
	#include "stm32f103_lcd_soft_iic_port.h"
#elif defined LCD_USE_HARD_IIC  //硬件IIC    
	#include "stm32f103_lcd_hard_iic_port.h"
#elif defined LCD_USE_DMA_IIC  //DMA_IIC驱动 (暂不支持)
	//#include "stm32f103_oled_dma_iic_port.h"
	#error ("stm32f103 dma iic driver is not supported!")
#endif





#if defined Wegui_USE_6KEY_PORT    //6键交互模式
	#include "stm32f103_Wegui_6key_port.h"
	#define Wegui_Interface_port_Init() do{Wegui_6key_port_Init();Wegui_Uart_Port_Init();}while(0)
#elif defined Wegui_USE_4KEY_PORT    //4键交互模式
	#include "stm32f103_Wegui_4key_port.h"
	#define Wegui_Interface_port_Init() do{Wegui_4key_port_Init();Wegui_Uart_Port_Init();}while(0)
#elif defined Wegui_USE_NONE_PORT
	#define Wegui_Interface_port_Init() do{}while(0)
	#define Wegui_Interface_stick(x) do{}while(0)
#endif
		
	
	
	


#if defined Wegui_UART_ON
	#include "stm32f103_Wegui_uart_port.h"
#else //defined Wegui_UART_OFF
	#define Wegui_Uart_Port_Init() do{}while(0) //防止编译错误
	#define Wegui_uart_rx_stick(stick) do{}while(0) //防止编译错误
#endif
	

	
	
	
	
#include "lcd_wegui_menu_app.h"
		
	
	
#endif
	
