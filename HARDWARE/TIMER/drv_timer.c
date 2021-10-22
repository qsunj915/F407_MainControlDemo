/**
  ******************************************************************************
  * @file    drv_timer.c
  * @author  
  * @date    21-5-25
  * @brief  
  ******************************************************************************
  */
#include "drv_timer.h"

uint16_t	G_delaytime_count = 0;
uint8_t		G_TIM7_status = 0;		//0为关闭，1为开启

/**
  * @brief  TIM2初始化
  * @param  arr自动重装载值
  *			psc预分频值
  * @note	参数值参考：8399,9--1ms
  * @retval 
  */
void TIM2_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //定时器2时钟使能

	//定时器2初始化
	TIM_TimeBaseStructure.TIM_Period		= arr;					//设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler		= psc;					//设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//递增计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             	//将结构参数用于初始化定时器2

	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE );           //使能定时器2更新中断

	//设置中断参数
	NVIC_InitStructure.NVIC_IRQChannel						= TIM2_IRQn;            		//定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER2_PreemptionPriority;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER2_SubPriority;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//使能中断通道
	NVIC_Init(&NVIC_InitStructure);//初始化中断
	TIM_Cmd(TIM2, ENABLE);//使能定时器
}

void TIM3_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //定时器2时钟使能

	//定时器2初始化
	TIM_TimeBaseStructure.TIM_Period		= arr;					//设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler		= psc;					//设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//递增计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             	//将结构参数用于初始化定时器2

	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE );           //使能定时器2更新中断

	//设置中断参数
	NVIC_InitStructure.NVIC_IRQChannel						= TIM3_IRQn;            		//定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER3_PreemptionPriority;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER3_SubPriority;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//使能中断通道
	NVIC_Init(&NVIC_InitStructure);//初始化中断
	TIM_Cmd(TIM3, ENABLE);//使能定时器
}

void TIM5_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //定时器2时钟使能

	//定时器2初始化
	TIM_TimeBaseStructure.TIM_Period		= arr;					//设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler		= psc;					//设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//递增计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             	//将结构参数用于初始化定时器2

	TIM_ITConfig(TIM5, TIM_IT_Update,ENABLE );           //使能定时器2更新中断

	//设置中断参数
	NVIC_InitStructure.NVIC_IRQChannel						= TIM5_IRQn;            		//定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER5_PreemptionPriority;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER5_SubPriority;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//使能中断通道
	NVIC_Init(&NVIC_InitStructure);//初始化中断
	TIM_Cmd(TIM5, ENABLE);//使能定时器
}



/**
  * @brief  TIM7延时功能定时器初始化
  * @param  time--延时时间ms
  * @note	
  * @retval 
  */
void TIM7_DelayFunction_ms_Init(void) {
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //定时器2时钟使能

	//定时器2初始化
	TIM_TimeBaseStructure.TIM_Period		= 8399;					//设置重载值
	TIM_TimeBaseStructure.TIM_Prescaler		= 9;					//设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision	= TIM_CKD_DIV1;			//设置分频因子
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;	//递增计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);             	//将结构参数用于初始化定时器2

	TIM_ITConfig(TIM7, TIM_IT_Update,ENABLE );           //使能定时器2更新中断

	//设置中断参数
	NVIC_InitStructure.NVIC_IRQChannel						= TIM7_IRQn;            		//定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= TIMER7_PreemptionPriority;	//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority			= TIMER7_SubPriority;			//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd					= ENABLE;						//使能中断通道
	NVIC_Init(&NVIC_InitStructure);//初始化中断
	TIM_Cmd(TIM7, DISABLE);//失能定时器
}


/**
  * @brief  TIM7延时函数
  * @param  time--延时时间ms
  * @note	
  * @retval 
  */
void TIM7_Delay_ms(const uint16_t time) {
	TIM7_Delay_Start();
	while (G_delaytime_count<time);
	TIM7_DelayCount_End();
//	Serial_Send(Serial1, "Delay_ms is OK!\r\n");
}


uint16_t Get_TIM7_CountTime(void) {
	return G_delaytime_count;
}

uint8_t TIM7_Delay_Start(void) {
	TIM_Cmd(TIM7, ENABLE);//使能定时器
	if ( !G_TIM7_status ) {
		G_TIM7_status = 1;
	} else {
		TIM7_ERRTask();
		return 0;
	}
	G_delaytime_count = 0;
	return 1;
}

void TIM7_DelayCount_Run(void) {
	G_delaytime_count++;
}

void TIM7_DelayCount_End(void) {
	TIM_Cmd(TIM7, DISABLE);//失能定时器
}

void TIM7_ERRTask(void)
{
	Serial_Send(Serial1, "Function **TIM7_Delay_Start** Corrupt!\r\n");
}

