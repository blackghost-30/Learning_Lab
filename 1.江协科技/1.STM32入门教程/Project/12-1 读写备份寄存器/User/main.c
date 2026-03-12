#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的读写备份寄存器工程
  * @brief        : 通过按键控制写入BKP的值，再直接读出BKP的值
  * @hardware     : STM32103C8T6 + OLED + 按键
  * @software     : Keil MDK + 标准外设库 + 按键封装模块，不封装BKP模块，直接在main.c中读写
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

uint8_t KeyNum;

uint16_t ArrayWrite[] = {0x1234, 0x5678};	// 写入的数组
uint16_t ArrayRead[2];

int main(void)
{
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "W:");
	OLED_ShowString(2, 1, "R:");
	
	
	// 初始化BKP
	// 第一步：开启PWR和BKP的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	// 第二步：使能对BKP和RTC的访问
	PWR_BackupAccessCmd(ENABLE);
	
	while (1)
	{
		KeyNum = Key_GetNum();
		
		if (KeyNum == 1)
		{
			ArrayWrite[0] ++;
			ArrayWrite[1] ++;
			
			BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);	// DR的值从1到10
			BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);
			
			OLED_ShowHexNum(1, 3, ArrayWrite[0], 4);
			OLED_ShowHexNum(1, 8, ArrayWrite[1], 4);
		}
		
		ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
		ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
		
		OLED_ShowHexNum(2, 3, ArrayRead[0], 4);
		OLED_ShowHexNum(2, 8, ArrayRead[1], 4);
	}
}
