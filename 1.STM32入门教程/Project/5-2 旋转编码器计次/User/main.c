#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的旋转编码器计次工程
  * @brief        : 基于STM32的外部中断系统实现旋转编码器计次
  * @hardware     : STM32103C8T6 + 旋转编码器 ，采用GPIO口连接旋转编码器输出
  * @software     : Keil MDK + 标准外设库，根据引脚的外部中断执行中断函数
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int16_t Num;			// 全局变量接收计数值

int main(void)
{
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1, 1, "Num:");
	
	while (1)
	{
		Num += Encoder_Get();				// 通过返回变化量来实现加减运算
		OLED_ShowSignedNum(1, 5, Num, 5);
	}
}
