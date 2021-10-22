/**
  ******************************************************************************
  * @file    pack_deal.c
  * @author  qsunj
  * @date    21-5-26
  * @brief  
  ******************************************************************************
  */
#include "pack_deal.h"


/******************数据格式******************
		帧头：“
		
中间数据：
		按键值：K1-K10，K21-K22，K11-K14
		电位计：ADC1-ADC8（K21，K22，K23-K26）
		
		帧尾：”
********************************************/
const uint8_t FRAMEHEAD		= '\"';
const uint8_t FRAMETAIL		= 0xee;

uint8_t tramsmitdata_buffer_key[ FRAMELENGTH_KEY ]		= {0};//键值暂存区
uint16_t transmitData_buffer_float[ FRAMELENGTH_FLOAT ]	= {0};//浮点数值缓冲区

uint8_t TransmitData_SendFrame[FRAMELENGTH]		= {0};//打包后的数据内存区
uint8_t TransmitData_ReceiveFrame[FRAMELENGTH]	= {0};//解包后的数据内存区


/**
  * @brief :获得解包后的数据
  * @param :可选参数：K1-K14;K23-K26;R_X,R_Y,L_X,L_Y
  * @note  :
  * @retval:无
  */ 
uint16_t Get_NRF_Deal_ReceiveData(TransmitDataLocateNum num) {
	uint16_t returndata=0;
	if ( num < R_X ) {
		Serial_Send(Serial1, "The param of Get_ReceiveData is error!\r\n");
		return 0;
	} else if ( num < K1 ) {
		returndata = TransmitData_ReceiveFrame[num+1];
		returndata |= TransmitData_ReceiveFrame[num+2]<<8;		
	} else if ( num < K9 ) {
		returndata += TransmitData_ReceiveFrame[K_PECK1+1] & (1 << (7-(num-K1)) );
	} else if ( num < K16 ){
		returndata += TransmitData_ReceiveFrame[K_PECK2+1] & (1 << (7-(num-K9)) );
	}
	return returndata;
}


/**
  * @brief :数据解包后的任务
  * @param :无
  * @note  :
  * @retval:无
  */ 
void ReceiveData_Task() {
	uint8_t i=0;
	
	for (i=0; i<FRAMELENGTH; i++) {
		Serial_SendByte(Serial1, TransmitData_ReceiveFrame[i]);
	}
}

void TransmitData_UnPack_CheckTask(uint8_t* buf, uint8_t len) {
	uint8_t i=0;
	for (i=0; i<len; i++) {
		TransmitData_UnPack( *(buf+i) );
	}
}

/**
  * @brief :数据打包函数
  * @param :无
  * @note  :打包后的数据存放在 TransmitData_SendFrame(数组) 中
  * @retval:旧版--不用了
  */ 
void TransmitData_Pack(void) {
	uint8_t i=0;
	uint8_t *TransmitData_SendFrame_temppoint = &TransmitData_SendFrame[2-1];
	
	for (i=0; i<FRAMELENGTH_KEY; i++) {
		TransmitData_SendFrame_temppoint[i] = tramsmitdata_buffer_key[i];
	}
	
	for (i=0; i<FRAMELENGTH_FLOAT; i++) {
		//低八位在前
		TransmitData_SendFrame_temppoint[FRAMELENGTH_KEY+2*i] = transmitData_buffer_float[i] & 0xff;
		TransmitData_SendFrame_temppoint[FRAMELENGTH_KEY+2*i+1] = transmitData_buffer_float[i] >> 8;
	}
	
	TransmitData_SendFrame[0]				= FRAMEHEAD;
	TransmitData_SendFrame[FRAMELENGTH-1]	= FRAMETAIL;
}


/**
  * @brief :数据解包函数
  * @param :无
  * @note  :解包后的数据存放在 TransmitData_RecevieFrame(数组) 中
  * @retval:无
  */ 
void TransmitData_UnPack(uint8_t receive_data) {
	static uint8_t transmit_processbit=0;//过程标志位:用于开始数据接收和控制接收数据的位置
	
	//接收数据主体程序
	if (receive_data==FRAMEHEAD && !transmit_processbit) {
		TransmitData_ReceiveFrame[transmit_processbit] = receive_data;
		transmit_processbit = 1;
	} else if (transmit_processbit>0) {
		TransmitData_ReceiveFrame[transmit_processbit] = receive_data;
		transmit_processbit++;
		if (transmit_processbit==FRAMELENGTH) {
			transmit_processbit = 0;
		}
	} else {
		transmit_processbit = 0;
	}
	
	//数据帧检查
	if (TransmitData_ReceiveFrame[FRAMELENGTH-1]==FRAMETAIL) {
		//ReceiveData_Task();
		TransmitData_ReceiveFrame[FRAMELENGTH-1] = 0x00;
	}
}

/**
  * @brief :键值的输入
  * @param :
  *			data:要输入的数据
  *			locate:数据的插入地址
  * @note  :
  * @retval:无
  */ 
void Insert_transmitdata_buffer_key(uint8_t data, uint8_t locate) {
	tramsmitdata_buffer_key[locate] = data;
}


/**
  * @brief :ADC值的输入
  * @param :
  *			data:要输入的数据
  *			locate:数据的插入地址
  * @note  :
  * @retval:无
  */ 
void Insert_transmitdata_buffer_float(uint16_t data, uint8_t locate) {
	transmitData_buffer_float[locate] = data;
}

