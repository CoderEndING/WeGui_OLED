#include "lcd_WeGui_Config.h"

#ifdef LCD_USE_SOFT_4SPI


#include "stm32f103_lcd_soft_4spi_port.h"
#include "lcd_driver.h"
#include "stdint.h"




static void SPI_send_8bitByte(uint8_t dat);



/*--------------------------------------------------------------
  * 名称: LCD_delay_ms(volatile uint32_t ms)
  * 传入1: ms
  * 返回: 无
  * 功能: 软件延时
  * 说明: 非精准
----------------------------------------------------------------*/
void LCD_delay_ms(volatile uint32_t ms)
{
	//delay_ms(ms);
	
		volatile uint16_t i;
		while (ms--) 
		{
			i = 10000; //根据实际情况调整
			while (i--);
		}
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_1Cmd(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个命令(DC=0时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_1Cmd(uint8_t dat)
{
	LCD_DC_Clr();
	LCD_CS_Clr();
	SPI_send_8bitByte(dat);
	LCD_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_1Dat(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: 向屏幕发送1个数据(DC=1时发1字节spi)
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_1Dat(uint8_t dat)
{
	LCD_DC_Set();
	LCD_CS_Clr();
	SPI_send_8bitByte(dat);
	LCD_CS_Set();
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_nDat(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个数据
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_nDat(uint8_t *p,uint16_t num)
{
	uint8_t i=0;
	LCD_DC_Set();
	LCD_CS_Clr();
	while(num>i)
	{
		SPI_send_8bitByte(p[i++]);	  
	}
	LCD_CS_Set();
}




#if defined (LCD_USE_NORMAL_OLED) || defined (LCD_USE_GRAY_OLED)
//-------------------------------------------以下是OLED屏幕专用驱动接口----------------------------------------------

/*--------------------------------------------------------------
  * 名称: LCD_Port_Init()
  * 传入: 无
  * 返回: 无
  * 功能: 屏幕接口初始化
  * 说明: 
----------------------------------------------------------------*/
void LCD_Port_Init(void)
{
	LCD_SCL_IO_Init();
	LCD_SDA_IO_Init();
	LCD_RES_IO_Init();
	LCD_DC_IO_Init();
	LCD_CS_IO_Init();
	
	#if defined(LCD_USE_DYNAMIC_REFRESH)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//动态刷新CRC校验用
	#endif
	
	LCD_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	LCD_RES_Set();
}
/*--------------------------------------------------------------
  * 名称: SPI_send_8bitByte(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: SPI发送1个字节数据
  * 说明: 
----------------------------------------------------------------*/
static void SPI_send_8bitByte(uint8_t dat)
{
//OLED SPI SCL默认常高,第二个跳变数据沿有效
	uint8_t i;
	for(i=0;i<8;i++)
	{			  
		LCD_SCL_Clr();
		if(dat&0x80)
		   LCD_SDA_Set();
		else 
		   LCD_SDA_Clr();
		dat<<=1; 
		LCD_SCL_Set();
	}		  
}

/*--------------------------------------------------------------
  * 名称: LCD_Send_nCmd(uint8_t *p,uint16_t num)
  * 传入1: *p数组指针
  * 传入2: num发送数量
  * 返回: 无
  * 功能: 向屏幕发送num个命令
  * 说明: 
----------------------------------------------------------------*/
void LCD_Send_nCmd(uint8_t *p,uint16_t num)
{
	uint8_t i=0;
	LCD_DC_Clr();
	LCD_CS_Clr();
	while(num>i)
	{
		SPI_send_8bitByte(p[i++]);	  
	}
	LCD_CS_Set();
}















//-------------------------------------------以下是RGB屏幕专用驱动接口----------------------------------------------
#elif defined (LCD_USE_RGB565)
void LCD_Port_Init(void)
{
	LCD_SCL_IO_Init();LCD_SCL_Set();
	LCD_SDA_IO_Init();
	LCD_RES_IO_Init();
	LCD_DC_IO_Init();
	LCD_CS_IO_Init();
	LCD_BL_IO_Init();
	
	#if defined(LCD_USE_DYNAMIC_REFRESH)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//动态刷新CRC校验用
	#endif
	
	
	LCD_RES_Clr();
	{
		volatile unsigned int i=10000;
		while(i--);
	}
	LCD_RES_Set();

}

/*--------------------------------------------------------------
  * 名称: SPI_send_8bitByte(uint8_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: SPI发送1个字节数据
  * 说明: 
----------------------------------------------------------------*/
static void SPI_send_8bitByte(uint8_t dat)
{
	//TFT SPI SCL默认常低,第一个跳变数据沿有效
	uint8_t i;
	for(i=0;i<8;i++)
	{			  
		if(dat&0x80)
		   LCD_SDA_Set();
		else 
		   LCD_SDA_Clr();
		LCD_SCL_Set();
		dat<<=1; 
		LCD_SCL_Clr();
	}		
}

/*--------------------------------------------------------------
  * 名称: SPI_send_16bitByte(uint16_t dat)
  * 传入1: dat
  * 返回: 无
  * 功能: SPI发送1个字节数据
  * 说明: 
----------------------------------------------------------------*/
static void SPI_send_16bitByte(uint16_t dat)
{
	//TFT SPI SCL默认常低,第一个跳变数据沿有效
	uint8_t i;
	for(i=0;i<16;i++)
	{			  
		if(dat&0x8000)
		   LCD_SDA_Set();
		else 
		   LCD_SDA_Clr();
		LCD_SCL_Set();
		dat<<=1; 
		LCD_SCL_Clr();
	}	    
}

/*--------------------------------------------------------------
  * 名称: void LCD_Send_nCmd(uint16_t *p,uint16_t num)
  * 传入1: uint16_t *p:要发送的"1位命令+n个数据"的数组起始地址
  * 传入2: uint16_t num "命令+数据"的总数量(数组的长度)
  * 返回: 无
  * 功能: 向SPI发送指令
  * 说明: 阻塞运行
----------------------------------------------------------------*/
void LCD_Send_nCmd(uint8_t *p,uint16_t num)
{
	//数组[0]按照指令发送
	//余下位按照数据发送
		
		//1.开始传输第一个命令
		LCD_DC_Clr();
		num--;
		LCD_CS_Clr();
		SPI_send_8bitByte(p[0]);
	
		//2.发送剩下的数据
		LCD_DC_Set();
		while(num-->0)
		{
			p++;
			SPI_send_8bitByte(*p);
		}
		//3.结束
		LCD_CS_Set();	
}


#endif








//----------------------------普通OLED屏幕刷屏接口-------------------------------------
#if defined (LCD_USE_NORMAL_OLED)

#if defined(LCD_USE_FULL_REFRESH)
//---------方式1:全屏刷新----------
//--优点:全屏刷新
//--缺点:内容不变的区域也参与了刷新
void LCD_Refresh(void)
{
	unsigned char ypage;
	for(ypage=0;ypage<GRAM_YPAGE_NUM;ypage++)
	{
		LCD_Set_Addr(0,ypage);
		LCD_Send_nDat(&lcd_driver.LCD_GRAM[ypage][0],SCREEN_WIDTH);
	}
}

#elif defined(LCD_USE_DYNAMIC_REFRESH)
//---------方式2:动态刷新----------
//--优点:性能好,按需区域刷新,节省MCU资源
//--缺点:全屏刷新相对变慢
void LCD_Refresh(void)
{
	//每page做"sum+mini_crc组合"校验,若校验码没变,则不刷新该page
	static uint32_t sum1[GRAM_YPAGE_NUM];
	unsigned char ypage,x;
	for(ypage=0;ypage<GRAM_YPAGE_NUM;ypage++)
	{
		uint32_t i_sum1;
		
		//-----方式1:CRC算法校验-----
		CRC->CR = CRC_CR_RESET;//CRC_ResetDR();
		for(x=0;x<SCREEN_WIDTH;x++)
		{
			CRC->DR = lcd_driver.LCD_GRAM[ypage][x];//CRC_CalcCRC(lcd_driver.LCD_GRAM[ypage][x]);
		}
		i_sum1 = CRC->DR;//i_sum1 = CRC_GetCRC();
		//---------------------------
		
		//-----方式2:累加乘积校验-----
		//i_sum1 = 0;
		//for(x=0;x<SCREEN_WIDTH;x++)
		//{
		//	i_sum1 = i_sum1 + (uint32_t)lcd_driver.LCD_GRAM[ypage][x]*x;
		//}
		//---------------------------
		
		if(sum1[ypage] != i_sum1)
		{
			LCD_Set_Addr(0,ypage);
			LCD_Send_nDat(&lcd_driver.LCD_GRAM[ypage][0],SCREEN_WIDTH);
		}
		sum1[ypage] = i_sum1;
	}
}
#endif

//----------------------------灰度OLED屏幕刷屏接口-------------------------------------
#elif defined (LCD_USE_GRAY_OLED)//灰度OLED
//---------方式1:全屏刷新----------
//--优点:全屏刷新
//--缺点:内容不变的区域也参与了刷新
void LCD_Refresh(void)
{
	unsigned char x,y,i;
	#if defined(GRAY_DRIVER_0DEG)
	//---扫描方向1(不旋转)----
	LCD_Set_Addr(0,0,(SCREEN_WIDTH/2-1),(SCREEN_HIGH-1));
	LCD_DC_Set();
	LCD_CS_Clr();
	for(y=0;y<SCREEN_HIGH;y++)
	{
		uint8_t page,mask;
		page=y/8;
		mask=(0x01<<y%8);
		for(x=0;x<SCREEN_WIDTH;)
		{
			i = 0x00;
			//第一个点
			if(lcd_driver.LCD_GRAM[page][x]&mask)
			{
				i = GRAY_COLOUR<<4;
			}
			x++;
			//第二个点
			if(x<SCREEN_WIDTH)
			{
				if(lcd_driver.LCD_GRAM[page][x]&mask)
				{
					i |= GRAY_COLOUR;
				}
			}
			x++;
			SPI_send_8bitByte(i);
		}
	}

	#elif defined(GRAY_DRIVER_90DEG)
	//---扫描方向2(90度旋转)---
	LCD_Set_Addr(0,0,(SCREEN_HIGH/2-1),(SCREEN_WIDTH-1));
	LCD_DC_Set();
	LCD_CS_Clr();
	for(y=0;y<SCREEN_HIGH;y+=2)
	{
		uint8_t page1,page2,mask1,mask2;
		page1=y/8;
		page2=(y+1)/8;
		mask1=(0x01<<y%8);
		mask2=(0x01<<(y+1)%8);
		for(x=0;x<SCREEN_WIDTH;x++)
		{
			i = 0x00;
			//第一个点
			if(lcd_driver.LCD_GRAM[page1][x]&mask1)
			{
				i = GRAY_COLOUR<<4;
			}
			//第二个点
			//if((y+1)<SCREEN_HIGH)
			{
				if(lcd_driver.LCD_GRAM[page2][x]&mask2)
				{
					i |= GRAY_COLOUR;
				}
			}
			SPI_send_8bitByte(i);
		}
	}
	#endif
	LCD_CS_Set();
}



//----------------------------RGB565屏幕刷屏接口-------------------------------------
#elif defined (LCD_USE_RGB565)
#if defined(LCD_USE_FULL_REFRESH)
//---------方式1:全屏从上往下刷----------
//--优点:全屏刷新
//--缺点:内容不变的区域也参与了刷新
void LCD_Refresh(void)
{
	uint16_t x,y;
	LCD_Set_Addr(0,0,SCREEN_WIDTH-1,SCREEN_HIGH-1);
	
	LCD_DC_Set();
	LCD_CS_Clr();
	for(y=0;y<SCREEN_HIGH;y++)
	{
		uint8_t mask=0x01<<(y%8);
		uint8_t page=y/8;
		for(x=0;x<SCREEN_WIDTH;x++)
		{
			if(lcd_driver.LCD_GRAM[page][x]&mask)
			{
				//绘图色
				SPI_send_16bitByte(LCD_DRAW_COLOUR);
			}
			else
			{
				//背景色
				SPI_send_16bitByte(LCD_CLEAR_COLOUR);
			}
		}
	}
	LCD_CS_Set();
}

#elif defined(LCD_USE_DYNAMIC_REFRESH)
//---------方式2:page校验从上往下刷----------
//--优点:性能好,按需区域刷新,节省MCU资源
//--缺点:全屏刷新会变慢,个别画面可能会刷错,图形错误撕裂
void LCD_Refresh(void)
{
	//每page做校验,若校验码没变,则不刷新该page
	static uint32_t sum1[GRAM_YPAGE_NUM];
	unsigned char ypage,x,ycount;
	for(ypage=0;ypage<GRAM_YPAGE_NUM;ypage++)
	{
		uint32_t i_sum1=0x0000;
		for(x=0;x<SCREEN_WIDTH;x++)
		{
			i_sum1 = i_sum1 + (uint32_t)lcd_driver.LCD_GRAM[ypage][x]*x;
		}
		if(sum1[ypage] != i_sum1)
		{
			uint8_t y=0;
			LCD_Set_Addr(0,ypage*8,SCREEN_WIDTH-1,SCREEN_HIGH-1);
			LCD_DC_Set();
			LCD_CS_Clr();
			ycount = 8* ypage;
			for(y=0;y<8;y++)
			{
				uint8_t mask=0x01<<(y%8);
				uint8_t x;
				if(++ycount >= SCREEN_HIGH){break;}
				for(x=0;x<SCREEN_WIDTH;x++)
				{
					if(lcd_driver.LCD_GRAM[ypage][x]&mask)
					{
						//绘图色
						SPI_send_16bitByte(LCD_DRAW_COLOUR);
					}
					else
					{
						//背景色
						SPI_send_16bitByte(LCD_CLEAR_COLOUR);
					}
				}
			}
			sum1[ypage] = i_sum1;
		}
	}
	LCD_CS_Set();
}
#endif

#endif






#endif
