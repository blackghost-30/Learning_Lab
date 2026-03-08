#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的光敏传感器控制蜂鸣器工程
  * @brief        : 基于STM32的GPIO口电平读取和设置进行蜂鸣器控制
  * @hardware     : STM32103C8T6 + 光敏传感器 + 蜂鸣器 ，采用GPIO口连接光敏传感器和蜂鸣器
  * @software     : Keil MDK + 标准外设库，根据光敏传感器引脚电平驱动蜂鸣器
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	Buzzer_Init();			// 初始化蜂鸣器引脚
	LightSensor_Init();		// 初始化光敏传感器引脚
	
	while (1)
	{
		if (LightSensor_Get() == 1)		// 若光敏传感器引脚为1则启动蜂鸣器
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
	}
}
