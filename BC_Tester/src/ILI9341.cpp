/*
 * ILI9341.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: mqvista
 */

#include <ILI9341.h>

ILI9341::ILI9341() {
	// TODO Auto-generated constructor stub

}

void ILI9341::Init() {
	m_lib_SPI.SPI1_Init();
	LCD_GPIO_Init();

	GPIO_ResetBits(GPIOA, DIS_RES);
	delay.delay_ms(50);
	GPIO_SetBits(GPIOA, DIS_RES);
	delay.delay_ms(50);

	WriteCommand(0xCF);
	WriteData(0x00);
	WriteData(0xC1);
	WriteData(0X30);

	WriteCommand(0xED);
	WriteData(0x64);
	WriteData(0x03);
	WriteData(0X12);
	WriteData(0X81);

	WriteCommand(0xE8);
	WriteData(0x85);
	WriteData(0x10);
	WriteData(0x78);

	WriteCommand(0xCB);
	WriteData(0x39);
	WriteData(0x2C);
	WriteData(0x00);
	WriteData(0x34);
	WriteData(0x02);

	WriteCommand(0xF7);
	WriteData(0x20);

	WriteCommand(0xEA);
	WriteData(0x00);
	WriteData(0x00);

	WriteCommand(0xC0);    	//Power control
	WriteData(0x21);   		//VRH[5:0]

	WriteCommand(0xC1);		//Power control
	WriteData(0x12);   		//SAP[2:0];BT[3:0]

	WriteCommand(0xC5);		//VCM control
	WriteData(0x32);
	WriteData(0x3C);

	WriteCommand(0xC7);		//VCM control2
	WriteData(0XA7); 		//B4

	WriteCommand(0x36);		// Memory Access Control
#ifdef DISPLAY_ROTATE_NORMAL
			WriteData(0x08);
#elif defined  DISPLAY_ROTATE_LEFT
	WriteData(0x48);
#elif defined DISPLAY_ROTATE_RIGHT
	WriteData(0x88);
#endif

	WriteCommand(0x3A);
	WriteData(0x55);

	WriteCommand(0xB1);
	WriteData(0x00);
	WriteData(0x17);

	WriteCommand(0xB6);		// Display Function Control
	WriteData(0x0A);
	WriteData(0xA2);

	WriteCommand(0xF6);
	WriteData(0x01);
	WriteData(0x30);

	WriteCommand(0xF2);		// 3Gamma Function Disable
	WriteData(0x00);

	WriteCommand(0x26);		//Gamma curve selected
	WriteData(0x01);

	WriteCommand(0xE0);		//Set Gamma
	WriteData(0x0F);
	WriteData(0x20);
	WriteData(0x1E);
	WriteData(0x07);
	WriteData(0x0A);
	WriteData(0x03);
	WriteData(0x52);
	WriteData(0X63);
	WriteData(0x44);
	WriteData(0x08);
	WriteData(0x17);
	WriteData(0x09);
	WriteData(0x19);
	WriteData(0x13);
	WriteData(0x00);

	WriteCommand(0XE1);		//Set Gamma
	WriteData(0x00);
	WriteData(0x16);
	WriteData(0x19);
	WriteData(0x02);
	WriteData(0x0F);
	WriteData(0x03);
	WriteData(0x2F);
	WriteData(0x13);
	WriteData(0x40);
	WriteData(0x01);
	WriteData(0x08);
	WriteData(0x07);
	WriteData(0x2E);
	WriteData(0x3C);
	WriteData(0x0F);
	WriteCommand(0x11);		//Exit Sleep
	delay.delay_ms(120);
	WriteCommand(0x29);		//Display on
}

void ILI9341::LCD_Clean(uint16_t Color) {
	uint32_t index = 0;
	LCD_SetCursor(0x00, 0x0000);    //设置光标位置
	LCD_WriteRAM_Prepare();
	for (index = 0; index < 320 * 320; index++) {
		WriteData(Color >> 8);
		WriteData(Color);
	}
}

//开始写GRAM
void ILI9341::LCD_WriteRAM_Prepare() {
	WriteCommand(0x2C);
}

//设定光标
void ILI9341::LCD_SetCursor(uint16_t Xpos, uint16_t Ypos) {
#ifdef DISPLAY_ROTATE_NORMAL
	WriteCommand(0x2A);
	WriteData(Xpos >> 8);
	WriteData(0xFF & Xpos);                //设定X坐标

	WriteCommand(0x2B);
	WriteData(Ypos >> 8);
	WriteData(0xFF & Ypos);//设定Y坐标
#elif defined  DISPLAY_ROTATE_LEFT
	WriteCommand(0x2A);
	WriteData(Ypos >> 8);
	WriteData(0xFF & Ypos);                //设定Y坐标

	WriteCommand(0x2B);
	WriteData(Xpos >> 8);
	WriteData(0xFF & Xpos);                //设定X坐标
#elif def		WriteCommand(0x2A);
	WriteData(Ypos >> 8);
	WriteData(0xFF & Ypos);                //设定Y坐标

	WriteCommand(0x2B);
	WriteData(Xpos >> 8);
	WriteData(0xFF & Xpos);//设定X坐标
#endif
}

void ILI9341::LCD_GPIO_Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DIS_A0 | DIS_RES;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_1);
}

void ILI9341::WriteCommand(uint8_t cmd) {
	GPIO_ResetBits(GPIOA, DIS_A0);
	m_lib_SPI.SPI1_ReadWriteByte(cmd);
}


void ILI9341::WriteData(uint8_t data) {
	GPIO_SetBits(GPIOA, DIS_A0);
	m_lib_SPI.SPI1_ReadWriteByte(data);
}

//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void ILI9341::LCD_Fill(uint16_t xsta, uint16_t xend, uint16_t ysta,
		uint16_t yend, uint16_t color) {
#ifdef DISPLAY_ROTATE_NORMAL
	uint16_t i,j;
	uint16_t xlen=0;
	xlen=xend-xsta+1;
	for(i=ysta;i<=yend;i++)
	{
		LCD_SetCursor(xsta,i);      //设置光标位置
		LCD_WriteRAM_Prepare();//开始写入GRAM
		for(j=0;j<xlen;j++)
		{
			WriteData(color>>8);
			WriteData(color);
		}
	}
#elif defined  DISPLAY_ROTATE_LEFT
	uint16_t i, j;
	uint16_t ylen = 0;
	ylen = yend - ysta + 1;
	for (i = xsta; i <= xend; i++) {
		LCD_SetCursor(ysta, i);      //设置光标位置
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for (j = 0; j < ylen; j++) {
			WriteData(color >> 8);
			WriteData(color);
		}
	}
#elif defined DISPLAY_ROTATE_RIGHT
	uint16_t i, j;
	uint16_t ylen = 0;
	ylen = yend - ysta + 1;
	for (i = xsta; i <= xend; i++) {
		LCD_SetCursor(ysta, i);      //设置光标位置
		LCD_WriteRAM_Prepare();//开始写入GRAM
		for (j = 0; j < ylen; j++) {
			WriteData(color >> 8);
			WriteData(color);
		}
	}
#endif
}

//画点
//x:0~239 / 0~319
//y:0~319 / 0~239
//color:此点的颜色
void ILI9341::LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
#ifdef DISPLAY_ROTATE_NORMAL
	LCD_SetCursor(x,y);
	LCD_WriteRAM_Prepare();
	WriteData(color>>8);
	WriteData(color);
#elif defined  DISPLAY_ROTATE_LEFT
	LCD_SetCursor(y, x);
	LCD_WriteRAM_Prepare();
	WriteData(color >> 8);
	WriteData(color);
#elif defined DISPLAY_ROTATE_RIGHT
	LCD_SetCursor(y,x);
	LCD_WriteRAM_Prepare();
	WriteData(color>>8);
	WriteData(color);
#endif
}

//在指定位置显示一个字符
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//在指定位置显示一个字符
//x:0~234
//y:0~308
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16
//mode:叠加方式(1)还是非叠加方式(0)
//void ILI9341::LCD_ShowChar(uint16_t x, uint16_t y, int8_t num, uint8_t size,
//		uint16_t color) {
//	u8 temp;
//	u8 pos, t;
//	//设置窗口
//	num = num - ' ';      //得到偏移后的值
//	for (pos = 0; pos < size; pos++) {
//		if (size == 12)
//			temp = asc2_1206[num][pos];      //调用1206字体
//		else
//			temp = asc2_1608[num][pos];		 //调用1608字体
//		for (t = 0; t < size / 2; t++) {
//			if (temp & 0x01)
//				LCD_DrawPoint(x + t, y + pos, color);		 //画一个点
//			temp >>= 1;
//		}
//	}
//}

void ILI9341::LCD_ShowChar_4824(uint16_t x, uint16_t y, int8_t num,
		uint16_t color) {
	uint8_t xpos, ypos;
	uint16_t startPOS = num * 144;
	for (xpos = 0; xpos < 24; xpos++) {
		LCD_SetCursor(x + xpos, y);
		LCD_WriteRAM_Prepare();
		for (ypos = 0; ypos < 48;) {
			for (uint8_t mask = 0x80; mask != 0; mask = mask >> 1) {
				if (*(((uint8_t *) asc2_4824) + startPOS) & mask) {
					WriteData(color >> 8);
					WriteData(color);
				} else {
					WriteData(0x00);
					WriteData(0x00);
				}
				ypos++;
			}
			startPOS++;
		}
	}
}

//显示字符串
//x,y:起点坐标
//*p:字符串起始地址
//用字体
void ILI9341::LCD_ShowString(uint16_t x, uint16_t y, uint16_t color,
		uint8_t *p) {
	while (*p != '\0') {
		LCD_ShowChar_4824(x, y, *p, color);
		x += 24;
		p++;
	}
}

//显示int数字
void ILI9341::LCD_ShowNum(uint16_t x, uint16_t y, uint16_t color,
		uint8_t length, const int32_t num) {
	uint8_t str[20];
	uint8_t numlen = 0;
	if (num < 10) {
		numlen = length - 1;
		uint8_t addLen = numlen;
		while (addLen--) {
			str[addLen] = ' ';
		}
	} else if (10 <= num && num < 100) {
		numlen = length - 2;
		uint8_t addLen = numlen;
		while (addLen--) {
			str[addLen] = ' ';
		}
	} else if (100 <= num && num < 1000) {
		numlen = length - 3;
		uint8_t addLen = numlen;
		while (addLen--) {
			str[addLen] = ' ';
		}
	} else if (1000 <= num && num < 10000) {
		numlen = length - 4;
		uint8_t addLen = numlen;
		while (addLen--) {
			str[addLen] = ' ';
		}
	} else if (10000 <= num && num < 100000) {
		numlen = length - 5;
		uint8_t addLen = numlen;
		while (addLen--) {
			str[addLen] = ' ';
		}
	}
	siprintf((char *) str + numlen, "%d", num);
	LCD_ShowString(x, y, color, str);
}

void ILI9341::LCD_ShowFloat(uint16_t x, uint16_t y, uint16_t color,
		uint8_t length, const float num) {
	uint8_t str[20];
	uConvert.byFloat(num, length, str);
	LCD_ShowString(x, y, color, str);
}
