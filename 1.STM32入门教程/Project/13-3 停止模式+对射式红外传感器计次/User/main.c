#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的停机模式+红外传感器计次工程
  * @brief        : 利用外部中断唤醒处于停机状态下的STM32
  * @hardware     : STM32103C8T6 + OLED + 红外传感器
  * @software     : Keil MDK + 标准外设库 + 模块封装 + 循环结尾加停机模式进入函数
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	CountSensor_Init();
	
	// 停止模式需要用到库函数，先使能PWR的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	OLED_ShowString(1, 1, "Count:");
	
	while (1)
	{
		OLED_ShowNum(1, 7, CountSensor_Get(), 5);
		
		// 闪烁字符串
		OLED_ShowString(2, 1, "Running");
		Delay_ms(100);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		// 调用函数进入停止模式
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		
		// 唤醒后会默认选择HSI的8MHz时钟，可调用下面函数将时钟重新配置为72MHz
		SystemInit();
	}
}
