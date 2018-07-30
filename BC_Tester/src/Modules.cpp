/*
 * Modules.cpp
 *
 *  Created on: 2018年3月6日
 *      Author: mqvista
 */

#include <Modules.h>

Modules *Modules::m_Instance = NULL;

Modules::Modules() {
	// TODO Auto-generated constructor stub

}

void Modules::Init() {
	utick.Init();
	button.Init();
	libADC.Init();
	libtimer.Init();
	ili9341.Init();
	ili9341.LCD_Clean(0x0000);
	battery.Init();

	Set_System();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
}

Modules* Modules::Instance() {
	if(m_Instance == NULL)
	{
		m_Instance = new Modules();
		return m_Instance;
	}
	return m_Instance;
}
