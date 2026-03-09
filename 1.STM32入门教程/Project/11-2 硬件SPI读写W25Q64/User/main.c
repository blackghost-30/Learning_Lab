#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的硬件SPI读写W25Q64工程
  * @brief        : 基于硬件I2C进行W25Q64的读写
  * @hardware     : STM32103C8T6 + OLED + W25Q64，采用硬件SPI读写
  * @software     : Keil MDK + 标准外设库，通信层(硬件SPI)、硬件驱动层和应用层三部分
  * @author       : blackghost
  * @date         : 2026-03-09
  * @version      : V1
  ******************************************************************************
  */

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite[] = {0x01, 0x02, 0x03, 0x04};	// 写入的数组
uint8_t ArrayRead[4];		// 读出的数组

int main(void)
{
	OLED_Init();
	W25Q64_Init();
	
	OLED_ShowString(1, 1, "MID:   DID:");
	OLED_ShowString(2, 1, "W:");
	OLED_ShowString(3, 1, "R:");
	
	W25Q64_ReadID(&MID, &DID);
	OLED_ShowHexNum(1, 5, MID, 2);
	OLED_ShowHexNum(1, 12, DID, 4);
	
	W25Q64_SectorErase(0x000000);
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);
	W25Q64_ReadData(0x000000, ArrayRead, 4);
	
	
	OLED_ShowHexNum(2, 3, ArrayWrite[0], 2);
	OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
	OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
	OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);
	
	OLED_ShowHexNum(3, 3, ArrayRead[0], 2);
	OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
	OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
	OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
	
	while (1)
	{
		
	}
}
