/*
 * LibSenser.h
 *
 *  Created on: 2018年3月9日
 *      Author: mqvista
 */

#ifndef LIBSENSER_H_
#define LIBSENSER_H_

#include <stm32f10x.h>
#include <Filter.h>

class LibSenser {
public:
	LibSenser();
	double GetSenserValue();
	bool GetSenserValue2(uint16_t* adValue, double* realValue);
	void real_value_offset_zero();
	void unitConvery();
	uint8_t getInchStatus();
private:
	uint16_t m_adc_value;
	double m_real_value ;
	Filter filter;
	double m_offset_value;
	//0 为mm， 1为inch
	uint8_t m_isInch;
	double m_InchCoefficient;

};

#endif /* LIBSENSER_H_ */
