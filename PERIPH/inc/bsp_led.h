#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx.h"
#include "drv_gpio.h"

typedef enum LEDs
{ 
  LED0   = 0x0001,
  LED1   = 0x0002,
  LED2   = 0x0004,
  LED3   = 0x0008
}LED_Typedef;


void LED_Init(void);
void LED_Task(LED_Typedef LEDx, uint32_t interval);

#endif

