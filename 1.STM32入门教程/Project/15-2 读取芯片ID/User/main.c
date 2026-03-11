#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6读取芯片ID工程
  * @brief        : 直接根据基地址读取芯片内部的ID号
  * @hardware     : STM32103C8T6 + OLED
  * @software     : Keil MDK + 标准外设库，直接读取地址内容
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	
	OLED_ShowString(1, 1, "F_SIZE:");
	OLED_ShowHexNum(1, 8, *((__IO uint16_t *)(0x1FFFF7E0)), 4);		// 闪存容量寄存器的基地址
	
	OLED_ShowString(2, 1, "U_ID:");
	OLED_ShowHexNum(2, 6, *((__IO uint16_t *)(0x1FFFF7E8)), 4);
	OLED_ShowHexNum(2, 11, *((__IO uint16_t *)(0x1FFFF7E8 + 0x02)), 4);
	OLED_ShowHexNum(3, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 0x04)), 8);
	OLED_ShowHexNum(4, 1, *((__IO uint32_t *)(0x1FFFF7E8 + 0x08)), 8);	// 加偏移显示不同的U_ID
	
	while (1)
	{
		
	}
}
