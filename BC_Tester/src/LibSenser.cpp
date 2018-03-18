/*
 * LibSenser.cpp
 *
 *  Created on: 2018年3月9日
 *      Author: mqvista
 */

#include <LibSenser.h>
#include "Modules.h"

LibSenser::LibSenser():filter(14) {
	// TODO Auto-generated constructor stub
	m_offset_value = 0;
}

double LibSenser::GetSenserValue() {
	m_adc_value = Modules::Instance()->libADC.Get_Value_OverSampling(0, 2);
	m_adc_value = filter.Get(m_adc_value);
	m_real_value = 0.0569343809311725 * (m_adc_value - 3220) + 1.3924236738910398;
	return m_real_value;
}

bool LibSenser::GetSenserValue2(uint16_t* adValue, double* realValue) {
	m_adc_value = Modules::Instance()->libADC.Get_Value_OverSampling(0, 2);
	m_adc_value = filter.Get(m_adc_value);
	m_real_value = 0.0569343809311725 * (m_adc_value - 3220) + 1.3924236738910398 + m_offset_value;
	*adValue = m_adc_value;
	*realValue = m_real_value/1000;
	return true;
}

void LibSenser::real_value_offset_zero() {
	if (m_offset_value != 0) {
		m_offset_value = 0;
	} else {
		m_offset_value = 0 - GetSenserValue();
	}
}
