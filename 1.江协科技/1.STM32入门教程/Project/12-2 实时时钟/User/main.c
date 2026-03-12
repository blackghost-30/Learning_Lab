#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的实时时钟工程
  * @brief        : 读取STM32的RTC寄存器获取时间
  * @hardware     : STM32103C8T6 + OLED
  * @software     : Keil MDK + 标准外设库 + 模块封装
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	
	OLED_ShowString(1, 1, "Date:xxxx-xx-xx");
	OLED_ShowString(2, 1, "Time:xx:xx:xx");
	OLED_ShowString(3, 1, "CNT :");
	OLED_ShowString(4, 1, "DIV :");
	
	while (1)
	{
		MyRTC_ReadTime();	// 调用后CNT的时间就会刷新到MyRTC_Time数组中
		
		OLED_ShowNum(1, 6, MyRTC_Time[0], 4);
		OLED_ShowNum(1, 11, MyRTC_Time[1], 2);
		OLED_ShowNum(1, 14, MyRTC_Time[2], 2);
		OLED_ShowNum(2, 6, MyRTC_Time[3], 2);
		OLED_ShowNum(2, 9, MyRTC_Time[4], 2);
		OLED_ShowNum(2, 12, MyRTC_Time[5], 2);
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
		
		// 显示余数寄存器，余数寄存器每自减一轮CNT就加一，通过余数寄存器可以获得比秒更小的单位
		OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	}
}
