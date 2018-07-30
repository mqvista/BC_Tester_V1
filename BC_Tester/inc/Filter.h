/*
 * Filter.h
 *
 *  Created on: 2018年3月8日
 *      Author: mqvista
 */

#ifndef FILTER_H_
#define FILTER_H_


#include <stm32f10x.h>

class Filter {
public:
	Filter(uint8_t size);
	~Filter();
	uint16_t Get(uint16_t value);
private:
	uint16_t* m_nums;
	uint8_t m_nums_sp;
	uint8_t m_size;
};

#endif /* FILTER_H_ */
