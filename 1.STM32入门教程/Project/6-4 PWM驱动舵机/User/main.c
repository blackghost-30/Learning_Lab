#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的PWM驱动舵机工程
  * @brief        : 基于STM32的PWM功能实现舵机驱动
  * @hardware     : STM32103C8T6 + 舵机 + OLED
  * @software     : Keil MDK + 标准外设库，封装PWM模块，主函数不断调用更改占空比的函数
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint8_t KeyNum;		// 定义用于接收键码的变量
float Angle;		// 定义角度变量

int main(void)
{
	OLED_Init();		// OLED初始化
	Servo_Init();		// 舵机初始化
	Key_Init();			// 按键初始化

	OLED_ShowString(1, 1, "Angle:");		// 1行1列显示字符串Angle:
	
	while (1)
	{
		KeyNum = Key_GetNum();	// 获取按键值，判断是否按下
		if (KeyNum == 1)		// 若按下
		{
			Angle += 30;		// 角度加30度
			if (Angle > 180)	// 若角度大于180度
			{
				Angle = 0;		// 清零
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1, 7, Angle, 3);
	}
}
