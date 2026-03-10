#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6修改主频工程
  * @brief        : 选择system_stm32f10x.c文件中的宏定义进行主频的修改
  * @hardware     : STM32103C8T6 + OLED
  * @software     : Keil MDK + 标准外设库
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	
	// 先打印一下系统的主频
	OLED_ShowString(1, 1, "SYSCLK:");
	OLED_ShowNum(1, 8, SystemCoreClock, 8);
	
	while (1)
	{
		// 闪烁字符串，可通过修改主频来变换闪烁的周期
		OLED_ShowString(2, 1, "Running");
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(500);
	}
}
