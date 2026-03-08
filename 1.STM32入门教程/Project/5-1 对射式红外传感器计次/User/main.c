#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的对射式红外传感器计次工程
  * @brief        : 基于STM32的外部中断系统实现红外传感器计次
  * @hardware     : STM32103C8T6 + 红外传感器 ，采用GPIO口连接红外传感器
  * @software     : Keil MDK + 标准外设库，根据引脚的外部中断执行中断函数
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();						// 初始化OLED屏幕
	CountSensor_Init();					// 初始化红外计数器，包括了外部中断配置
	
	OLED_ShowString(1, 1, "Count:");
	
	while (1)
	{
		OLED_ShowNum(1, 7, CountSensor_Get(), 5);
	}
}
