/**
  ******************************************************************************
  * @file	drv_usart.h
  * @author	qsunj
  * @date	21-5-21
  * @brief   
  ******************************************************************************
  */

#ifndef __DRV_UART_H
#define __DRV_UART_H

#include "drv_gpio.h"
#include "drv_nvic.h"
#include <stdio.h>
#include <stdarg.h>

#define Serial1 USART1
#define Serial3 USART3

typedef USART_TypeDef Serial_TypeDef;

void USART1_Init(uint32_t baudrate);
void USART2_Init(uint32_t baudrate);
void USART3_Init(uint32_t baudrate);
void Serial_SendByte(Serial_TypeDef *Serialx, uint8_t Data);

void Serial_Send(Serial_TypeDef *Serialx,const char *Data,...);
char *itoa(int value, char *string, int radix);


#endif
