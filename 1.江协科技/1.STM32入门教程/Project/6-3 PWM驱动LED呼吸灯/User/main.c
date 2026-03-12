#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的PWM驱动呼吸灯工程
  * @brief        : 基于STM32的PWM功能实现呼吸灯
  * @hardware     : STM32103C8T6 + LED
  * @software     : Keil MDK + 标准外设库，封装PWM模块，主函数不断调用更改占空比的函数
  * @author       : blackghost
  * @date         : 2026-03-08
  * @version      : V1
  ******************************************************************************
  */

uint8_t i;			// 定义一个变量用于存放CCR寄存器的值

int main(void)
{
	OLED_Init();	// 初始化OLED屏幕
	PWM_Init();		// 初始化PWM
	
	while (1)			// 不断循环改变CCR寄存器的值
	{
		for (i = 0; i <= 100; i++)		// CCR寄存器的值不断自增，实现LED呼吸灯的变亮过程
		{
			PWM_SetCompare1(i);			// 调用改变CCR寄存器值的函数改变CCR寄存器的值
			Delay_ms(10);				// Delay10ms，防止变化太快
		}
		
		for (i = 0; i <= 100; i++)		// CCR寄存器的值不断自减，实现LED呼吸灯的变暗过程
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}
	}
}
