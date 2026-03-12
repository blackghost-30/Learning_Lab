#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的输入捕获测频率工程
  * @brief        : 基于STM32的输入捕获功能测量频率
  * @hardware     : STM32103C8T6 + OLED + TIM2 + TIM3
  * @software     : Keil MDK + 标准外设库，封装输入捕获模块，TIM2输出PWM，TIM3输入捕获测量其频率
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	PWM_Init();
	IC_Init();
	
	OLED_ShowString(1, 1, "Freq:00000Hz");
	
	// 下面两句将待测信号输出到PA0
	PWM_SetPrescaler(720 - 1);		// Freq = 72M / (PSC + 1) / (ARR + 1)(现在ARR + 1是100)
	PWM_SetCompare1(50);			// Duty = CCR / (ARR + 1)
	
	while (1)		// 不断循环改变CCR寄存器的值
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);		// 不断刷新频率显示
	}
}
