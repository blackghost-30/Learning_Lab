#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的读取内部FLASH工程
  * @brief        : 利用SRAM数组和FLASH的掉电不丢失实现数据备份
  * @hardware     : STM32103C8T6 + OLED + 按键
  * @software     : Keil MDK + 标准外设库 + 模块封装，采用底层 + 中间业务层 + 应用层的框架
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	Key_Init();
	Store_Init();	// 初始化，将闪存备份的数据加载回SRAM数组
	
	OLED_ShowString(1, 1, "Flag:");
	OLED_ShowString(2, 1, "Data:");
	
	while (1)
	{
		KeyNum = Key_GetNum();
		
		if (KeyNum == 1)			// 按下按键1就保存参数数据
		{
			Store_Data[1] ++;		// 记住不要使用第0位，是标志位
			Store_Data[2] += 2;
			Store_Data[3] += 3;
			Store_Data[4] += 4;
			Store_Save();			// 将SRAM数组备份回去给闪存
		}
		
		if (KeyNum == 2)			// 按键2按下则全部清零
		{
			Store_Clear();
		}
		
		OLED_ShowHexNum(1, 6, Store_Data[0], 4);	// 显示标志位
		OLED_ShowHexNum(3, 1, Store_Data[1], 4);
		OLED_ShowHexNum(3, 6, Store_Data[2], 4);
		OLED_ShowHexNum(4, 1, Store_Data[3], 4);
		OLED_ShowHexNum(4, 6, Store_Data[4], 4);
	}
}
