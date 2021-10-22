/**
  ******************************************************************************
  * @file	drv_nvic.h
  * @author	qsunj
  * @date	21-5-21
  * @brief   
  ******************************************************************************
  */
  
#ifndef __DRV_NVIC_H
#define __DRV_NVIC_H

/*-----------------NVIC_Init-----------------*/
#define NVIC_Priority_Init() NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2)


/*-----------------USART-----------------*/
#define USART1_PreemptionPriority  3;
#define USART1_SubPriority         0;

#define USART2_PreemptionPriority  3;
#define USART2_SubPriority         1;

#define USART3_PreemptionPriority  3;
#define USART3_SubPriority         2;

#define USART6_PreemptionPriority  3;
#define USART6_SubPriority         3;


/*-----------------TIMER-----------------*/
#define TIMER2_PreemptionPriority  2;
#define TIMER2_SubPriority         3;

#define TIMER3_PreemptionPriority  2;
#define TIMER3_SubPriority         2;

#define TIMER4_PreemptionPriority  2;
#define TIMER4_SubPriority         1;

#define TIMER5_PreemptionPriority  2;
#define TIMER5_SubPriority         0;

#define TIMER7_PreemptionPriority  0;
#define TIMER7_SubPriority         0;

/*-----------------TIMER-----------------*/
#define EXTI4_PreemptionPriority	1;
#define EXTI4_SubPriority			0;

/*-----------------DMA-----------------*/
#define DMA2_PreemptionPriority    0;
#define DMA2_SubPriority           1;
 


#endif
