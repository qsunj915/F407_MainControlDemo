/**
  ******************************************************************************
  * @file    drv_spi.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-02-23
  * @brief   deive for hardware spi
						 硬件SPI配置 软件待加入
						 void drv_spi_init( void )  SPI初始化
						 uint8_t drv_spi_read_write_byte( uint8_t TxByte ) SPI收发一个字节
						 void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )  SPI收发字符串

  ******************************************************************************
  */
	
#include "drv_spi.h"

#ifndef __USE_SOFT_SPI_INTERFACE__

/** 硬件SPI */
#define SPI_WAIT_TIMEOUT			((uint16_t)0x00FF)

/**
  * @brief :SPI初始化(硬件)
  * @param :无
  * @note  :无
  * @retval:无
  */ 
void drv_spi_init( void )
{
	SPI_InitTypeDef		SpiInitStructer;
	
	/** SPI引脚配置 */
	GPIO_Format_Init(GPIOB,SPI_CLK_GPIO_PIN | SPI_MISO_GPIO_PIN | SPI_MOSI_GPIO_PIN ,GPIO_Mode_AF\
					,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_50MHz);

	GPIO_PinAFConfig(SPI_CLK_GPIO_PORT,GPIO_PinSource13,GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT,GPIO_PinSource14,GPIO_AF_SPI2);
	GPIO_PinAFConfig(SPI_MISO_GPIO_PORT,GPIO_PinSource15,GPIO_AF_SPI2);

	GPIO_SetBits( SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN );

	/*-------------nss写在nrf24l01------------------ */
	GPIO_Format_Init(GPIOA, SPI_NSS_GPIO_PIN,GPIO_Mode_OUT\
					,GPIO_OType_PP,GPIO_PuPd_UP,GPIO_Speed_100MHz);

	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN );		//置高

	/** SPI配置 */
	SPI_I2S_DeInit( SPI_PORT );			//复位SPI
	
	if( SPI1 == SPI_PORT | SPI4 == SPI_PORT | SPI5 == SPI_PORT | SPI6 == SPI_PORT )				
	{
		RCC_APB2PeriphClockCmd( SPI_PORT_CLK, ENABLE );			//SPI1在APB2上，打开相应SPI时钟
	}
	else
	{
		RCC_APB1PeriphClockCmd( SPI_PORT_CLK, ENABLE );			//SPI2 3在APB1上
	}
	
	SPI_Cmd( SPI_PORT, DISABLE );		//关闭SPI外设，配置前关闭
	
	SpiInitStructer.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;    //双线全双工
	SpiInitStructer.SPI_Mode              = SPI_Mode_Master;                    //主机模式
	SpiInitStructer.SPI_CPOL              = SPI_CPOL_Low;                       //空闲状态为低电平 
	SpiInitStructer.SPI_CPHA              = SPI_CPHA_1Edge;                     //第一个边沿采集数据
	SpiInitStructer.SPI_DataSize          = SPI_DataSize_8b;                    //8位数据
	SpiInitStructer.SPI_NSS               = SPI_NSS_Soft;                       //从机软件管理
	SpiInitStructer.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;            //64分频
	SpiInitStructer.SPI_FirstBit          = SPI_FirstBit_MSB;                   //最高位先发送
	SpiInitStructer.SPI_CRCPolynomial     = 7;                                  //CRC多项式,默认不使用SPI自带CRC	 
	
	SPI_Init( SPI_PORT, &SpiInitStructer );
	SPI_Cmd( SPI_PORT, ENABLE );
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	uint8_t l_Data = 0;
	uint16_t l_WaitTime = 0;
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_TXE ) )		//等待发送缓冲区为空
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//如果等待超时则退出
		}
	}
	l_WaitTime = SPI_WAIT_TIMEOUT / 2;		//重新设置接收等待时间(因为SPI的速度很快，正常情况下在发送完成之后会立即收到数据，等待时间不需要过长)
	SPI_PORT->DR = TxByte;	//发送数据
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_RXNE ) )		//等待接收缓冲区非空
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//如果等待超时则退出
		}
	}
	
	l_Data = (uint8_t)SPI_PORT->DR;		//读取接收数据
	
	return l_Data;		//返回
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	GPIO_ResetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);	  		//拉低片选
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//收发数据
		ReadBuffer++;
		WriteBuffer++;			                                    	//读写地址加1
	}
	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				  //拉高片选
}

/** 硬件SPI */
#endif



