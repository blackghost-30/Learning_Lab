#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include <string.h>						// C语言官方的字符串库

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的串口收发文本数据包工程
  * @brief        : 基于封装的串口外设进行数据包收发
  * @hardware     : STM32103C8T6 + OLED + USB转串口模块
  * @software     : Keil MDK + 标准外设库 + 模块封装 + 串口助手，中断中用状态机实现数据包解析
  * @author       : blackghost
  * @date         : 2026-03-11
  * @version      : V1
  ******************************************************************************
  */

uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	Serial_Init();
	LED_Init();
	
	OLED_ShowString(1, 1, "TxPacket:");
	OLED_ShowString(3, 1, "RxPacket:");
	
	while (1)
	{
		if (Serial_RxFlag == 1)		// 若接收到数据包
		{
			OLED_ShowString(4, 1, "                ");		// 擦除第四行
			OLED_ShowString(4, 1, Serial_RxPacket);			// 第四行显示接收到的数据
			
			if (strcmp(Serial_RxPacket, "LED_ON") == 0)		// 字符串比较，若相等进入分支
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_ON_OK");
			}
			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)		// 字符串比较，若相等进入分支
			{
				LED1_OFF();
				Serial_SendString("LED_ON_OFF\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else		// 若都不匹配则显示指令错误
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
			
			Serial_RxFlag = 0;		// 在这里将其置零，避免数据包错位
		}
	}
}
