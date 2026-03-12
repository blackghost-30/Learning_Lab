#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的睡眠模式+串口发送+接收工程
  * @brief        : 利用串口的外部中断工程唤醒处于睡眠状态下的STM32
  * @hardware     : STM32103C8T6 + OLED + USB转串口模块 + 串口助手
  * @software     : Keil MDK + 标准外设库 + 模块封装 + 循环结尾加__WFI()
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
		if (Serial_GetFlag() == 1)		// 用自己封装的标志位判断
		{
			RxData = Serial_GetRxData();		// 调用自己的函数读取
			Serial_SendByte(RxData);			// 数据回传功能
			OLED_ShowHexNum(1, 1, RxData, 2);
		}
		
		// 闪烁字符串
		OLED_ShowString(2, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		__WFI();
		// 每来一个中断先进中断函数再从这里开始继续运行
	}
}
