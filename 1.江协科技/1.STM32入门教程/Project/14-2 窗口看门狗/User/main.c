#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的窗口看门狗工程
  * @brief        : 利用STM32的窗口看门狗实现自动复位
  * @hardware     : STM32103C8T6 + OLED + 按键
  * @software     : Keil MDK + 标准外设库 + 按键模块封装，用按键的阻塞来延迟喂狗实现复位
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "WWDG TEST");
	
	// 判断复位是看门狗导致的复位还是复位按键导致的复位
	if (RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		// 若是看门狗导致的复位就闪烁字符串
		OLED_ShowString(2, 1, "WWDGST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "      ");
		Delay_ms(100);
		RCC_ClearFlag();	// 清除标志位，需要手动
	}
	else
	{
		// 若是复位按键导致的复位就闪烁另外一个字符串
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(3, 1, "   ");
		Delay_ms(100);
	}
	
	// 第一步：开启APB1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	// 第二步：设置预分频和窗口值，这里选择50ms，对应的预分频系数和重装值可通过公式计算
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);		// 窗口值为30ms，同时需要将W6位置1，所以需要或上
	
	// 第三步：使能
	WWDG_Enable(0x40 | 54);     // 首次写一个重装值，同时需要将T6位置1，所以需要或上
	
	while (1)
	{
		Key_GetNum();			// 按住按键不放主循环就会阻塞，不能及时喂狗，就会产生复位
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(20);
		OLED_ShowString(4, 1, "    ");
		Delay_ms(20);
		
		WWDG_SetCounter(0x40 | 54);		// 不断喂狗
	}
}
