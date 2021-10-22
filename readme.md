# README

## TIPS:

* 使用前注意
    * 宏定义：options -> C/C++ -> 在Define中加入STM32F40_41xxx
    * 添加新功能之前要注意Pin不要重复
* 目前存在的问题
    * 长时间运行时可能会出现程序莫名卡死



### 功能&一些函数的说明：

* LED：LED_Task() ==> 用于在中断中切换led灯状态
    * para:LED编号，切换led灯状态所需要的进入中断的次数
* NRF：
    * NRF24L01_RxPacket() ==> 接受通信数据
    * TransmitData_UnPack_CheckTask() ==> 检查接受的数据 & 将通信的数据存入 *TransmitData_ReceiveFrame*
    * Get_NRF_Deal_ReceiveData() ==> 读取通信接收的数据
        * 参数：要读取的数据编号（与遥控器上的按钮编号对应）



## Pins:

| Pin  | Func          |
| ---- | ------------- |
| A1   | NRF_CE        |
| A2   | USART2        |
| A3   | USART2        |
| A4   | NRF_IRQ&EXTI4 |
| A9   | USART1        |
| A10  | USART1        |
| B10  | USART3        |
| B11  | USART3        |
| B12  | SPI_NSS       |
| B13  | SPI_SCL       |
| B14  | SPI_MISO      |
| B15  | SPI_MOSI      |
| C0   | LED0          |
| C1   | LED1          |
| C2   | LED2          |
| C3   | LED3          |
| D0   | KEY0          |



<div align='right'> 2021/10/22</div>
<div align='right'> qsunj</div>

