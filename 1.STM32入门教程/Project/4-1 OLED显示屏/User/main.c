#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的OLED屏幕驱动工程
  * @brief        : 基于软件I2C进行OLED屏幕驱动
  * @hardware     : STM32103C8T6 + 四引脚OLED屏幕，采用PB8和PB9驱动
  * @software     : Keil MDK + 标准外设库 + OLED_Font.h，采用字模库显示
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 12345, 5);
	OLED_ShowSignedNum(2, 7, -66, 2);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	
	while (1)
	{
		
	}
}
