/**
  ******************************************************************************
  * @file	drv_gpio.h
  * @author	qsunj
  * @date	21-5-21
  * @brief   
  ******************************************************************************
  */
#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include "stm32f4xx.h"
#include "drv_nvic.h"

uint8_t GPIO_Format_Init(GPIO_TypeDef *GPIOX, uint16_t PinX, GPIOMode_TypeDef Mode, \
					GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed);

uint8_t Set_GPIOMapControler(GPIO_TypeDef *GPIOX, uint16_t PinX);
void Reset_GPIOMapControler(GPIO_TypeDef *GPIOX, uint16_t PinX);

#endif

