#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的AD多通道工程
  * @brief        : 基于STM32的ADC功能采样多个设备电压
  * @hardware     : STM32103C8T6 + OLED + 四个传感器模块
  * @software     : Keil MDK + 标准外设库，封装AD转换模块
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint16_t AD0, AD1, AD2, AD3;

int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "AD0:");
	OLED_ShowString(2, 1, "AD1:");
	OLED_ShowString(3, 1, "AD2:");
	OLED_ShowString(4, 1, "AD3:");
	
	while (1)
	{
		AD0 = AD_GetValue(ADC_Channel_0);
		AD1 = AD_GetValue(ADC_Channel_1);
		AD2 = AD_GetValue(ADC_Channel_2);
		AD3 = AD_GetValue(ADC_Channel_3);
		
		OLED_ShowNum(1, 5, AD0, 4);
		OLED_ShowNum(2, 5, AD1, 4);
		OLED_ShowNum(3, 5, AD2, 4);
		OLED_ShowNum(4, 5, AD3, 4);
		Delay_ms(100);				// 延时一小段时间防止刷新过快
	}
}
