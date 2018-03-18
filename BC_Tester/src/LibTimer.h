/*
 * LibTimer.h
 *
 *  Created on: 2018年3月1日
 *      Author: mqvista
 */

#ifndef LIBTIMER_H_
#define LIBTIMER_H_

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "Battery.h"

extern "C" {void TIM2_IRQHandler(void);}

class LibTimer {
public:
	LibTimer();
	void Init();
private:
	void LibTimer_NVIC_Init();
};

#endif /* LIBTIMER_H_ */
