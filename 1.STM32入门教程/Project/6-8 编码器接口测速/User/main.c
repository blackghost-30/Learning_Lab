#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的编码器接口测速
  * @brief        : 基于STM32的编码器接口测量正交波形
  * @hardware     : STM32103C8T6 + OLED + 编码器
  * @software     : Keil MDK + 标准外设库，封装编码器模块
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */
  
int16_t Speed;			// 定义一个计数变量

int main(void)
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();

	OLED_ShowString(1, 1, "Speed:");

	while (1)
	{
		// 主循环中不要放入Delay函数，防止阻塞
		OLED_ShowSignedNum(1, 7, Speed, 5);		// 打印速度，用这个函数可以显示负数
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update == SET))	// 检查中断标志位
	{
		Speed = Encoder_Get();							// 用Speed返回这个时间内的计数值
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		// 手动清空标志位，放置重复进入中断
	}
}
