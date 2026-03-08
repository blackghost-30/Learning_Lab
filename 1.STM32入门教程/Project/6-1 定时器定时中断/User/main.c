#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的定时器定时中断工程
  * @brief        : 基于STM32的中断系统系统实现定时器定时中断
  * @hardware     : STM32103C8T6 + OLED，采用定时器的中断系统每隔固定时间进一次中断
  * @software     : Keil MDK + 标准外设库
  * @author       : blackghost
  * @date         : 2026-03-08
  * @version      : V1
  ******************************************************************************
  */

uint16_t Num;		// 定义一个计数变量

int main(void)
{
	OLED_Init();
	Timer_Init();

	OLED_ShowString(1, 1, "Num:");

	while (1)
	{
		OLED_ShowNum(1, 5, Num, 5);		// 打印次数
	}
}

void TIM2_IRQHandler(void)				// 中断函数名都是固定的，所以要去启动文件中找
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update == SET))	// 检查中断标志位
	{
		Num ++;		// 每进一次中断自动++
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		// 手动清空标志位，防止重复进入中断
	}
}
