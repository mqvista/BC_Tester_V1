/*
 * LibADC.h
 *
 *  Created on: 2018年2月28日
 *      Author: mqvista
 */

#ifndef LIBADC_H_
#define LIBADC_H_

#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include <math.h>

class LibADC {
public:
	LibADC();
	void Init();
	uint16_t Get_Value(uint8_t ch);
	uint16_t Get_Value_OverSampling(uint8_t ch, uint8_t nums);
	uint16_t offsetValue;
};

#endif /* LIBADC_H_ */
