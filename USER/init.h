/**
  ******************************************************************************
  * @file    init.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-03-30
  * @brief   Í·ÎÄ¼þ
						 

  ******************************************************************************
  */
	
#ifndef __INIT_H
#define __INIT_H

#include "stm32f4xx.h"
#include "drv_systick.h"
#include "drv_timer.h"
#include "drv_usart.h"
#include "drv_spi.h"
#include "bsp_led.h"
#include "bsp_nrf24l01.h"
#include "pack_deal.h"
#include "drv_exti.h"

void System_Init(void);

#endif
