/**
  ******************************************************************************
  * @file    drv_gpio.c
  * @author  qsunj
  * @date    21-5-21
  * @brief  
  ******************************************************************************
  */
  
#include "drv_gpio.h"

const uint8_t GPIOPORTMAX	= 5;

uint16_t G_GPIO_map[GPIOPORTMAX] = {0};


/**
  * @brief  GPIO初始化，将结构体的成员初始化输入函数，引脚处可用或运算
  * @param  GPIOX  :  GPIOA~E
			PinX   ： GPIO_Pin_1~15 || GPIO_Pin_All
		    Mode   :  GPIO_Mode_IN || GPIO_Mode_OUT || GPIO_Mode_AF || GPIO_Mode_AN
			OType  :  GPIO_OType_PP || GPIO_OType_OD
			PuPd   ： GPIO_PuPd_NOPULL || GPIO_PuPd_UP || GPIO_PuPd_DOWN
		    Speed  :  GPIO_Speed_2MHz || GPIO_Speed_25MHz || GPIO_Speed_50MHz || GPIO_Speed_100MHz
  * @retval 0:		正常；
			非0：	不正常
  */
uint8_t GPIO_Format_Init(GPIO_TypeDef *GPIOX, uint16_t PinX, GPIOMode_TypeDef Mode, \
					GPIOOType_TypeDef OType, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/***************RCC****************/
	if (IS_GPIO_ALL_PERIPH(GPIOX)) {
		if (GPIOX==GPIOA) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		} else if (GPIOX==GPIOB) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		} else if (GPIOX==GPIOC) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		} else if (GPIOX==GPIOD) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		} else if (GPIOX==GPIOE) {
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		} else {
			return 1;
		}
	}

		
	/***************Pin****************/
	GPIO_InitStructure.GPIO_Pin = PinX;
	
	/***************Mode****************/
	if (IS_GPIO_MODE(Mode)) {
		GPIO_InitStructure.GPIO_Mode = Mode;
	} else {
		return 3;
	}
	
	/***************OType****************/
	if (IS_GPIO_OTYPE(OType)) {
		GPIO_InitStructure.GPIO_OType = OType;
	} else {
		return 4;
	}
	
	/***************PuPd****************/
	if (IS_GPIO_PUPD(PuPd)) {
		GPIO_InitStructure.GPIO_PuPd = PuPd;
	} else {
		return 5;
	}
	
	/***************Pin****************/
	if (IS_GPIO_SPEED(Speed)) {
		GPIO_InitStructure.GPIO_Speed = Speed;
	} else {
		return 6;
	}
	
	GPIO_Init(GPIOX, &GPIO_InitStructure);
	Set_GPIOMapControler(GPIOX, PinX);
	
	return 0;
}

/**
  * @brief  置位GPIOMap
  * @param  GPIOX  :  GPIOA~E
			PinX   ： GPIO_Pin_1~15 || GPIO_Pin_All
  * @retval 
  */
uint8_t Set_GPIOMapControler(GPIO_TypeDef *GPIOX, uint16_t PinX) {
	uint8_t GPIOx=0;
	uint16_t temp_gpioportmap = 0;
	
	if (GPIOX==GPIOA) {
		GPIOx = 0;
	} else if (GPIOX==GPIOB) {
		GPIOx = 1;
	} else if (GPIOX==GPIOC) {
		GPIOx = 2;
	} else if (GPIOX==GPIOD) {
		GPIOx = 3;
	} else if (GPIOX==GPIOE) {
		GPIOx = 4;
	} else {
		return 1;
	}

	temp_gpioportmap = G_GPIO_map[GPIOx];
	G_GPIO_map[GPIOx] |= PinX;
	
	if (temp_gpioportmap == G_GPIO_map[GPIOx]) {
		return 1;
	}
	return 0;
	
}

/**
  * @brief  清零GPIOMap
  * @param  GPIOX  :  GPIOA~E
			PinX   ： GPIO_Pin_1~15 || GPIO_Pin_All
  * @retval 
  */
void Reset_GPIOMapControler(GPIO_TypeDef *GPIOX, uint16_t PinX) {
	uint8_t GPIOx = 0;
	
	if (GPIOX==GPIOA) {
		GPIOx = 0;
	} else if (GPIOX==GPIOB) {
		GPIOx = 1;
	} else if (GPIOX==GPIOC) {
		GPIOx = 2;
	} else if (GPIOX==GPIOD) {
		GPIOx = 3;
	} else if (GPIOX==GPIOE) {
		GPIOx = 4;
	} else {
		return;
	}

	G_GPIO_map[GPIOx] &= 0xffff-PinX;
	
}

