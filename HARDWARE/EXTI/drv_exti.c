/**
  ******************************************************************************
  * @file    drv_exti.c
  * @author  qsunj
  * @date    21-6-6
  * @brief  
  ******************************************************************************
  */
#include "drv_exti.h"


void EXTI4_Init(void) {
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//初始化IO口
	GPIO_Format_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_IN, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_100MHz);
	
	//建立映射关系
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);
	
	EXTI_InitStructure.EXTI_Line 	= EXTI_Line4;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode 	= EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStruct.NVIC_IRQChannel						= EXTI4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd					= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= EXTI4_PreemptionPriority;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority			= EXTI4_SubPriority;
	NVIC_Init(&NVIC_InitStruct);
}
