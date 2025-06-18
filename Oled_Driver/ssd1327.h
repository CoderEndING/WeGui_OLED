#ifndef __SSD1327_H__
#define __SSD1327_H__

	
#define SSD1327_Set_Column_Address(start,end) do{LCD_Send_1Cmd(0x15);LCD_Send_1Cmd(start);LCD_Send_1Cmd(end);}while(0)//15h start[0:127]Ĭ��0,end[0:127]Ĭ��127

#define SSD1327_Set_Row_Address(start,end) do{LCD_Send_1Cmd(0x75);LCD_Send_1Cmd(start);LCD_Send_1Cmd(end);}while(0)//75h start[0:7F]Ĭ��0,end[0:7F]Ĭ��7F

#define SSD1327_Set_Contrast_Control(x) do{LCD_Send_1Cmd(0x81);LCD_Send_1Cmd(x);}while(0)//81h ���öԱȶ�[0:255]Ĭ��127

#define SSD1327_Set_Remap(x) do{LCD_Send_1Cmd(0xA0);LCD_Send_1Cmd(x);}while(0)			//A0h ������Ļӳ��λ�� Ĭ��0x00

#define SSD1327_Set_Display_Start_Line(x) do{LCD_Send_1Cmd(0xA1);LCD_Send_1Cmd(x);}while(0)			//A1h [0:127]Ĭ��0

#define SSD1327_Set_Display_Offset(x) do{LCD_Send_1Cmd(0xA2);LCD_Send_1Cmd(x);}while(0)			//A2h [0:127]Ĭ��0


#define SSD1327_Set_Display_Mode_A4() do{LCD_Send_1Cmd(0xA4);}while(0)			//A4h Normal display (RESET)
#define SSD1327_Set_Display_Mode_A5() do{LCD_Send_1Cmd(0xA5);}while(0)			//A5h All ON (All pixels have gray scale of 15, GS15)
#define SSD1327_Set_Display_Mode_A6() do{LCD_Send_1Cmd(0xA6);}while(0)			//A6h All OFF (All pixels have gray scale of 0, GS0)
#define SSD1327_Set_Display_Mode_A7() do{LCD_Send_1Cmd(0xA7);}while(0)			//A7h Inverse Display (GS0 -> GS15, GS1 -> GS14, GS2 -> GS13, ...)

#define SSD1327_Set_MUX_Ratio(x) do{LCD_Send_1Cmd(0xA8);LCD_Send_1Cmd(x);}while(0)	//A8h [15:127] 15=16MUX;127=128MUX(Ĭ��)


#define SSD1327_Func_A_Select_external_VDD() do{LCD_Send_1Cmd(0xAB);LCD_Send_1Cmd(0);}while(0)	//ABh 0x00
#define SSD1327_Func_A_Select_internal_VDD() do{LCD_Send_1Cmd(0xAB);LCD_Send_1Cmd(1);}while(0)	//ABh 0x01 Ĭ��

#define SSD1327_Display_OFF()	do{LCD_Send_1Cmd(0xAE);}while(0)									//AEh ��Ļ��,����(Ĭ��)
#define SSD1327_Display_ON()	do{LCD_Send_1Cmd(0xAF);}while(0)						      //AFh ��Ļ��

#define SSD1327_Set_Phase_Length(Phase_1,Phase_2) do{LCD_Send_1Cmd(0xB1);LCD_Send_1Cmd((Phase_2<<4)|Phase_1);}while(0)		//B1h ��ŵ�����(����1[0:15],����2[0:15]), Ĭ��(7,8)

#define SSD1327_NOP1() do{LCD_Send_1Cmd(0xB2);}while(0)		//B2h

#define Set_Front_Clock_Frequency(x) do{LCD_Send_1Cmd(0xB3);LCD_Send_1Cmd(x);}while(0)		//B3h [0x00:0xFF] Ĭ��0x00 b7~b4���þ��� b3~b0���÷�Ƶ

#define GPIO_Hiz_input_dis()    do{LCD_Send_1Cmd(0xB5);LCD_Send_1Cmd(0x00);}while(0)//B5h 0x00
#define GPIO_Hiz_input_en()     do{LCD_Send_1Cmd(0xB5);LCD_Send_1Cmd(0x01);}while(0)//B5h 0x01 
#define GPIO_Hiz_output_Low()   do{LCD_Send_1Cmd(0xB5);LCD_Send_1Cmd(0x02);}while(0)//B5h 0x02 Ĭ��
#define GPIO_Hiz_output_High()  do{LCD_Send_1Cmd(0xB5);LCD_Send_1Cmd(0x03);}while(0)//B5h 0x03

#define Set_Gray_Scale_Table(y0,y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13,y14,y15) do{LCD_Send_1Cmd(0xB8);LCD_Send_1Cmd(y0);LCD_Send_1Cmd(y1);LCD_Send_1Cmd(y2);LCD_Send_1Cmd(y3);LCD_Send_1Cmd(y4);LCD_Send_1Cmd(y5);LCD_Send_1Cmd(y6);LCD_Send_1Cmd(y7);LCD_Send_1Cmd(y8);LCD_Send_1Cmd(y9);LCD_Send_1Cmd(y10);LCD_Send_1Cmd(y11);LCD_Send_1Cmd(y12);LCD_Send_1Cmd(y13);LCD_Send_1Cmd(y14);LCD_Send_1Cmd(y15);}while(0)//B8h �Ҷ�����

//B9
	
#define SSD1327_NOP2() do{LCD_Send_1Cmd(0xBB);}while(0)		//BBh

#define SSD1327_Set_Pre_charge_voltage(x) do{LCD_Send_1Cmd(0xBC);LCD_Send_1Cmd(x);}while(0)		//BCh [0x00,0x0F] Ĭ��0x05
	
#define SSD1327_Set_VCOMH(x) do{LCD_Send_1Cmd(0xBE);LCD_Send_1Cmd(x);}while(0)		//BEh [0x00,0x0F] Ĭ��0x05


#define dis_2_precharge  0 //Ĭ��
#define en_2_precharge   1
#define Internal_VSL   0 //Ĭ��
#define external_VSL   1
#define SSD1327_Func_Selection_B(sec_pre,VSL) do{LCD_Send_1Cmd(0xD5);LCD_Send_1Cmd(0x60|(sec_pre<<1)|VSL);}while(0)		//D5h Ĭ��(0x0,0x0)

#define SSD1327_Set_Command_Lock()   do{LCD_Send_1Cmd(0xFD);LCD_Send_1Cmd(0x12);}while(0)		//FDh 0x16
#define SSD1327_Set_Command_unLock() do{LCD_Send_1Cmd(0xFD);LCD_Send_1Cmd(0x12);}while(0)		//FDh 0x12 (Ĭ��)





void SSD1327_Set_Addr_x(unsigned char x0,unsigned char x1);
void SSD1327_Set_Addr_y(unsigned char y0,unsigned char y1);
void SSD1327_Set_Addr(unsigned char x0,unsigned char x1,unsigned char y0,unsigned char y1);
void SSD1327_Init(void);



#endif

