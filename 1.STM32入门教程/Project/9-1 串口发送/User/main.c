#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的串口发送工程
  * @brief        : 调用官方标准外设库的函数进行硬件串口发送
  * @hardware     : STM32103C8T6 + OLED + USB转串口模块
  * @software     : Keil MDK + 标准外设库 + 模块封装
  * @author       : blackghost
  * @date         : 2026-03-10
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	OLED_Init();
	Serial_Init();
	
	// 验证发送字节的函数
	Serial_SendByte(0x41);
	
	// 验证发送数组的函数
	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	Serial_SendArray(MyArray, 4);
	
	// 验证发送字符串和发送数字的函数
	Serial_SendString("\r\nNum1=");
	Serial_SendNumber(111, 3);
	
	// 第一种printf重定向的方法
	printf("\r\nNum2=%d", 222);
	
	// 第二种，用sprintf函数
	char String[100];
	sprintf(String, "\r\nNum3=%d", 333);
	Serial_SendString(String);
	
	// 第三种：封装sprintf()函数
	Serial_Printf("\r\nNum4=%d", 444);
	Serial_Printf("\r\n");
	

/*******************************************************************************
	发送汉字的两种方式：
	第一种：需要在C/C++中添加--no-multibyte-chars，并都选择UTF-8格式
	第二种：两者都使用GB开头的中文编码格式，参数不用加
	Serial_Printf("你好，世界");
*******************************************************************************/
	
	while (1)
	{
		
	}
}
