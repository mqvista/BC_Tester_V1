/*
 * Modules.h
 *
 *  Created on: 2018年3月6日
 *      Author: mqvista
 */

#ifndef MODULES_H_
#define MODULES_H_

#include "ILI9341.h"
#include "UTick.h"
#include "LibTimer.h"
#include "LibADC.h"
#include "LibSPI.h"
#include "Battery.h"
#include "Button.h"
#include "LibSenser.h"

class Modules {
public:
	static Modules *Instance();
	void Init();
	UTick utick;
	LibTimer libtimer;
	Battery battery;
	ILI9341 ili9341;
	Button button;
	LibADC libADC;
	LibSenser libSenser;
private:
	static Modules *m_Instance;
	Modules();
};

#endif /* MODULES_H_ */
