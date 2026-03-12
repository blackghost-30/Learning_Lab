#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的待机模式+实时时钟工程
  * @brief        : 利用闹钟事件唤醒处于待机状态下的STM32
  * @hardware     : STM32103C8T6 + OLED + 跳线
  * @software     : Keil MDK + 标准外设库 + 闹钟设定 + 待机模式进入函数 + 硬件关闭
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	
	// 开启PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "CNT :");		// 显示秒计数器
	OLED_ShowString(2, 1, "ALR :");		// 显示闹钟值
	OLED_ShowString(3, 1, "ALRF :");	// 闹钟标志位
	
	// 这里不需要GPIO初始化，WU引脚高电平有效，断开时默认为下拉输入，所以为低电平
	PWR_WakeUpPinCmd(ENABLE);
	
	uint32_t Alarm = RTC_GetCounter() + 10;		// 获取闹钟秒数值
	RTC_SetAlarm(RTC_GetCounter() + 10);		// 设定闹钟为10秒后
	OLED_ShowNum(2, 6, Alarm, 10);
	
	while (1)
	{
		OLED_ShowNum(1, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(3, 6, RTC_GetFlagStatus(RTC_FLAG_ALR), 1);		// 显示闹钟标志位
		
		// 闪烁字符串
		OLED_ShowString(4, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(100);
		
		// 闪烁字符串
		OLED_ShowString(4, 1, "STANDBY");
		Delay_ms(1000);
		OLED_ShowString(4, 1, "       ");
		Delay_ms(100);
		
		// 在进入待机模式前需要将其他硬件外设断电，这样才省电
		OLED_Clear();
		
		PWR_EnterSTANDBYMode();
	}
}
