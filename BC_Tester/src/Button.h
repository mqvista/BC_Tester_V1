/*
 * button.h
 *
 *  Created on: 2018年2月27日
 *      Author: mqvista
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "UTick.h"

#define PWR_ON	GPIO_Pin_9
#define ChSta	GPIO_Pin_10
#define STDSta	GPIO_Pin_11
#define Key3	GPIO_Pin_12
#define Key2	GPIO_Pin_13
#define Key1	GPIO_Pin_14

extern "C" {
	void EXTI15_10_IRQHandler(void);
}


class Button {
public:
	Button();
	void Init();
private:
	void Button_GPIO_Init();
	void Button_Exti_Init();
	void Button_Nvic_Init();
};

#endif /* BUTTON_H_ */
