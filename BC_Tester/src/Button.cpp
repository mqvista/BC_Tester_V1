/*
 * button.cpp
 *
 *  Created on: 2018年2月27日
 *      Author: mqvista
 */

#include <Button.h>
#include "Modules.h"



Button::Button() {
	// TODO Auto-generated constructor stub

}

void Button::Init() {
	Button_GPIO_Init();
	Button_Exti_Init();
	Button_Nvic_Init();

}

void Button::Button_GPIO_Init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = ChSta | STDSta | Key3 | Key2 | Key1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

	GPIO_InitStructure.GPIO_Pin = PWR_ON;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_SetBits(GPIOB, PWR_ON);
//	GPIO_SetBits(GPIOB, PWR_ON);
}

void Button::Button_Exti_Init() {

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line =  EXTI_Line12 | EXTI_Line13 | EXTI_Line14 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line =  EXTI_Line12 | EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void Button::Button_Nvic_Init() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


extern "C" {
void EXTI15_10_IRQHandler(void) {

	if (EXTI_GetITStatus(EXTI_Line14) != RESET) {
		if (GPIO_ReadInputDataBit(GPIOB, Key1) != RESET) {
			Modules::Instance()->utick.Wait(1);
			if (GPIO_ReadInputDataBit(GPIOB, Key1) != RESET)
				GPIO_ResetBits(GPIOB, PWR_ON);
		}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
	if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
		if (GPIO_ReadInputDataBit(GPIOB, Key3) == RESET) {
			Modules::Instance()->libSenser.real_value_offset_zero();
		}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
	if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	if (EXTI_GetITStatus(EXTI_Line10) != RESET) {
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}
}
