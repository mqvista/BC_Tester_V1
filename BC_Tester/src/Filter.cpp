/*
 * Filter.cpp
 *
 *  Created on: 2018年3月8日
 *      Author: mqvista
 */

#include <Filter.h>

Filter::Filter(uint8_t size) {
	m_size = size;
	m_nums = new uint16_t[m_size];
	m_nums_sp = 0;
}

Filter::~Filter() {
	delete[] m_nums;
}

uint16_t Filter::Get(uint16_t value) {
	uint64_t sum=0;
	m_nums[m_nums_sp++] = value;
	m_nums_sp = m_nums_sp % m_size;
	for (uint8_t i = 0; i < m_size; i++)
	{
		sum+=m_nums[i];
	}
	return sum/m_size;
}
