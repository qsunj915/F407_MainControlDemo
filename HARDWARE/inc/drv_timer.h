/**
  ******************************************************************************
  * @file	drv_timer.h
  * @author	
  * @date	21-5-25
  * @brief   
  ******************************************************************************
  */

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H

#include "drv_gpio.h"
#include "drv_usart.h"

void TIM2_Init(uint16_t arr, uint16_t psc);
void TIM3_Init(uint16_t arr, uint16_t psc);
void TIM5_Init(uint16_t arr, uint16_t psc);

void TIM7_DelayFunction_ms_Init(void);
void TIM7_Runtimetest_Scheduler(uint8_t comm);

void TIM7_Delay_ms(const uint16_t time);
void TIM7_ERRTask(void);
uint16_t Get_TIM7_CountTime(void);

uint8_t TIM7_Delay_Start(void);
void TIM7_DelayCount_Run(void);
void TIM7_DelayCount_End(void);


#endif
