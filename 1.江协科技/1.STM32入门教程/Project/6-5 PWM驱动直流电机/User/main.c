#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的PWM驱动直流电机工程
  * @brief        : 基于STM32的PWM功能实现直流电机驱动
  * @hardware     : STM32103C8T6 + OLED + TB6612 + 直流电机
  * @software     : Keil MDK + 标准外设库，底层为PWM，中间业务层为Motor，应用层不断调用更改占空比的函数
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint8_t KeyNum;		// 获取键码
int8_t Speed;		// 定义速度，-100到100

int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "Speed:");

	while (1)					// 不断循环改变CCR寄存器的值
	{
		KeyNum = Key_GetNum();	// 获取键码
		if (KeyNum == 1)		// 判断是否按下按键
		{
			Speed += 20;		// 按下按键则速度自加20
			if (Speed > 100)	// 如果达到了最大速度，则反转至最大速度
			{
				Speed = -100;
			}
		}
		Motor_SetSpeed(Speed);				// 设置速度
		OLED_ShowNum(1, 7, Speed, 3);		// 打印速度
	}
}
