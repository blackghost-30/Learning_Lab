#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的独立看门狗工程
  * @brief        : 利用看门狗实现硬件自动复位
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
	
	OLED_ShowString(1, 1, "IWDG TEST");
	
	// 判断复位是看门狗导致的复位还是复位按键导致的复位
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		// 若是看门狗导致的复位就闪烁字符串
		OLED_ShowString(2, 1, "IWDGST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "      ");
		Delay_ms(100);
		RCC_ClearFlag();		// 清除标志位，需要手动
	}
	else
	{
		// 若是复位按键导致的复位就闪烁另外一个字符串
		OLED_ShowString(3, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(3, 1, "   ");
		Delay_ms(100);
	}
	
	// 初始化看门狗
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);	// 写使能，即解除写保护
	IWDG_SetPrescaler(IWDG_Prescaler_16);			// 配置预分频，这里选择16分频
	IWDG_SetReload(2499);							// 配置重装值，这样时间就是1000ms
	
	// 先喂一次狗
	IWDG_ReloadCounter();		// 即CNT的初始值即为重装值2499
	
	IWDG_Enable();				// 启动看门狗
	while (1)
	{
		Key_GetNum();			// 按住按键不放主循环就会阻塞，不能及时喂狗，就会产生复位
		
		IWDG_ReloadCounter();	// 喂狗
		
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(200);
		OLED_ShowString(4, 1, "    ");
		Delay_ms(600);
	}
}
