/*
 * LibTimer.cpp
 *
 *  Created on: 2018年3月1日
 *      Author: mqvista
 */

#include <LibTimer.h>
#include "Modules.h"

LibTimer::LibTimer() {
	// TODO Auto-generated constructor stub

}

void LibTimer::Init() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// 3600 = 1S
	TIM_TimeBaseStructure.TIM_Period = 3600 -1;
	//TIM2 36Mhz/10000 = 3600hz
	TIM_TimeBaseStructure.TIM_Prescaler = 10000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update ,ENABLE);
	TIM_Cmd(TIM2, ENABLE);

	LibTimer_NVIC_Init();
}

void LibTimer::LibTimer_NVIC_Init() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

extern "C" {
	void TIM2_IRQHandler(void){

		if ( Modules::Instance()->battery.BatUpdateFlag == false)
		{
			Modules::Instance()->battery.BatUpdateFlag = true;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
