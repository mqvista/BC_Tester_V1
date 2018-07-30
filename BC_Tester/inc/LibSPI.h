/*
 * LibSPI.h
 *
 *  Created on: 2018年2月23日
 *      Author: mqvista
 */

#ifndef LIBSPI_H_
#define LIBSPI_H_
#include "stm32f10x_spi.h"

class Lib_SPI {
public:
	Lib_SPI();
	void SPI1_Init();
	uint8_t SPI1_ReadWriteByte(uint8_t TxData);
};

#endif /* LIBSPI_H_ */
