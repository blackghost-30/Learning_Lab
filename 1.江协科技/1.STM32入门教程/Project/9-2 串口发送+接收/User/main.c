#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的串口发送+接收工程
  * @brief        : 调用官方标准外设库的函数进行硬件串口发送和接收
  * @hardware     : STM32103C8T6 + OLED + USB转串口模块
  * @software     : Keil MDK + 标准外设库 + 模块封装 + 串口助手
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

uint8_t RxData;

int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "RxData:");
	
	Serial_Init();
	
	
	// 不断判断RXNE标志位，置1则读取
	while (1)
	{
		if (Serial_GetFlag() == 1)				// 用自己封装的标志位判断
		{
			RxData = Serial_GetRxData();		// 调用自己的函数读取
			Serial_SendByte(RxData);			// 数据回传功能
			OLED_ShowHexNum(1, 1, RxData, 2);
		}
	}
}
