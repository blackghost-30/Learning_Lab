#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的按键控制LED工程
  * @brief        : 基于STM32的GPIO口电平读取和设置进行按键控制LED
  * @hardware     : STM32103C8T6 + 按键 + LED ，采用GPIO口连接按键和LED
  * @software     : Keil MDK + 标准外设库，采用库函数直接读取和控制GPIO口电平
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

uint8_t KeyNum;					// 定义一个全局变量来获取按键的返回值

int main(void)
{
	LED_Init();					// 初始化LED，其本质是使能LED对应引脚的时钟
	Key_Init();                 // 初始化Key，其本质是使能Key对应引脚的时钟
	
	while (1)
	{
		KeyNum = Key_GetNum(); 		// 用KeyNum接收按键的返回值，返回GPIO口电平
		if (KeyNum == 1)			// 如果当前按下的按键是1，则LED1取反
		{
			LED1_Turn();
		}
		if (KeyNum == 2)			// 如果当前按下的按键是2，则LED2取反
		{
			LED1_Turn();
		}
	}
}
