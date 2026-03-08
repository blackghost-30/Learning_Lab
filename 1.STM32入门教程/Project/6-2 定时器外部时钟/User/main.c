#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的定时器外部时钟工程
  * @brief        : 基于STM32的定时器中断和红外传感器实现定时器外部时钟
  * @hardware     : STM32103C8T6 + OLED + 红外传感器
  * @software     : Keil MDK + 标准外设库，红外遮挡十次产生一个更新中断
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
	OLED_ShowString(2, 1, "CNT:");

	while (1)
	{
		OLED_ShowNum(1, 5, Num, 5);						//打印次数
		OLED_ShowNum(2, 5, Timer_GetCounter(), 5);		//打印CNT的值
	}
}

void TIM2_IRQHandler(void)				// 中断函数名都是固定的，所以要去启动文件中找
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update == SET))		// 检查中断标志位
	{
		Num ++;			// 每进一次中断自动++
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);			// 手动清空标志位，防止重复进入中断
	}
}
