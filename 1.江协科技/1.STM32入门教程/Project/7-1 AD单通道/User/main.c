#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的AD单通道工程
  * @brief        : 基于STM32的ADC功能采样电压
  * @hardware     : STM32103C8T6 + OLED + 电位调节其
  * @software     : Keil MDK + 标准外设库，封装AD转换模块
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint16_t ADValue;		// 定义变量获取转换值
float Voltage;			// 定义变量用于获取真实电压值

int main(void)
{
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Voltage:0.00V");
	
	while (1)
	{
		ADValue = AD_GetValue();					// 调用函数返回转换值
		Voltage = (float)ADValue / 4095 * 3.3;		// 线性关系直接获得真实电压值
		
		OLED_ShowNum(1, 9, ADValue, 4);				// 打印转换结果
		
		// OLED无法显示浮点数，下面两条语句通过分开显示的操作来显示浮点数
		OLED_ShowNum(2, 9, Voltage, 1);
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2);
		
		Delay_ms(100);			//延时一小段时间防止刷新过快
	}
}
