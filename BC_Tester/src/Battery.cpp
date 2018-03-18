/*
 * Battery.cpp
 *
 *  Created on: 2018年3月1日
 *      Author: mqvista
 */

#include <Battery.h>
#include "Modules.h"

Battery::Battery() {
	// TODO Auto-generated constructor stub

}

void Battery::Init() {
	LibTimer libTimer;
	libTimer.Init();
	ReflushDisplay();
	BatUpdateFlag = false;
}

void Battery::ReflushDisplay() {
	float voltage = GetVoltage() * 0.0016;
	//Modules::Instance()->ili9341.LCD_ShowNum(150, 10, 0x07E0, 5, GetVoltage());
	Modules::Instance()->ili9341.LCD_ShowFloat(100,10,0x07E0, 1, voltage);
}

uint16_t Battery::GetVoltage() {
	uint16_t vtg = 0;
	for (int i=0; i<10; i++)
	{
		vtg += Modules::Instance()->libADC.Get_Value(1);
	}
	return vtg/10;
}
