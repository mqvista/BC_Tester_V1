/*
 * Battery.h
 *
 *  Created on: 2018年3月1日
 *      Author: mqvista
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include <stm32f10x.h>

//extern bool BatUpdateFlag;

class Battery {
public:
	Battery();
	void Init();
	uint16_t GetVoltage();
	void ReflushDisplay();
	bool BatUpdateFlag;
};

#endif /* BATTERY_H_ */
