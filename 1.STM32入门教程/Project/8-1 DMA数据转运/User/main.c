#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的DMA数据转运工程
  * @brief        : 基于STM32的DMA实现数据转运
  * @hardware     : STM32103C8T6 + OLED
  * @software     : Keil MDK + 标准外设库，封装DMA转运模块
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};		// 定义源端数组
uint8_t DataB[] = {0, 0, 0, 0};					// 定义目的数组

int main(void)
{
	// 初始化硬件
	OLED_Init();
	
	MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);		// 强制类型转换是为了取它们的地址
	
	// 显示最开始的数据
	OLED_ShowString(1, 1, "DataA");
	OLED_ShowString(3, 1, "DataB");
	OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8);
	OLED_ShowHexNum(3, 8, (uint32_t)DataA, 8);	

	while (1)
	{
		DataA[0] ++;
		DataA[1] ++;
		DataA[2] ++;
		DataA[3] ++;
		
		// 在第二行显示DataA的数据
		OLED_ShowHexNum(2, 1, DataA[0], 2);
		OLED_ShowHexNum(2, 4, DataA[1], 2);
		OLED_ShowHexNum(2, 7, DataA[2], 2);
		OLED_ShowHexNum(2, 10, DataA[3], 2);
	
		// 在第四行显示DataB的数据
		OLED_ShowHexNum(4, 1, DataB[0], 2);
		OLED_ShowHexNum(4, 4, DataB[1], 2);
		OLED_ShowHexNum(4, 7, DataB[2], 2);
		OLED_ShowHexNum(4, 10, DataB[3], 2);
		
		Delay_ms(1000);
		
		MyDMA_Transfer();
		
		// 在第二行显示转运后DataA的数据
		OLED_ShowHexNum(2, 1, DataA[0], 2);
		OLED_ShowHexNum(2, 4, DataA[1], 2);
		OLED_ShowHexNum(2, 7, DataA[2], 2);
		OLED_ShowHexNum(2, 10, DataA[3], 2);
	
		// 在第四行显示转运后DataB的数据
		OLED_ShowHexNum(4, 1, DataB[0], 2);
		OLED_ShowHexNum(4, 4, DataB[1], 2);
		OLED_ShowHexNum(4, 7, DataB[2], 2);
		OLED_ShowHexNum(4, 10, DataB[3], 2);
		
		Delay_ms(1000);
	}
}
