/**
  ******************************************************************************
  * @file    init.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-03-30
  * @brief   System_Init(void);
						 

  ******************************************************************************
  */

#include "init.h"

/**
  * @brief  system init
  * @param  none
  * @retval 无
  */
void System_Init(void)
{
	SystemInit();
	NVIC_Priority_Init();
	SysTick_Init();

	TIM7_DelayFunction_ms_Init();
	
	USART1_Init(115200);
	USART2_Init(115200);
	USART3_Init(115200);
	Serial_Send(Serial1, "USART is OK!\r\n");

	LED_Init();
	
	/*********NRF配置*********/
	NRF24L01_Gpio_Init();
	EXTI4_Init();
	
	//检测nRF24L01
	NRF24L01_check( );
	RF24L01_Init( );
	//接收模式
	RF24L01_Set_Mode( MODE_RX );
		
	RF24L01_SET_CS_LOW( );		//片选
	drv_spi_read_write_byte( FLUSH_RX );
	TIM7_Delay_ms( 1 );
	RF24L01_SET_CS_HIGH( );
	TIM7_Delay_ms( 1 );

	/****************************/
	

	TIM2_Init(8399, 9);		//1ms
	TIM3_Init(8399, 49);	//5ms
	TIM5_Init(8399, 199);	//20ms
	Serial_Send(Serial1, "Timer is OK!\r\n");
	
	Serial_Send(Serial1, "All Init is OK!\r\n");
}


