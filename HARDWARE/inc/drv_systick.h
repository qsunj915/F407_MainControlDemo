/**
  ******************************************************************************
  * @file    drv_systick.c
  * @author  qsunj
  * @date    21-5-23
  * @brief  
  ******************************************************************************
  */

#ifndef __DRV_SYSTICK_H
#define __DRV_SYSTICK_H

#include "stm32f4xx.h"

void SysTick_Init(void);
void delay_us(u32 time);
void delay_ms(u32 time);

#endif
