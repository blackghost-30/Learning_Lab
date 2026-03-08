#include "stm32f10x.h"                  // Device header

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的工程模板
  * @brief        : 基于ST官方的标准外设库构建的STM32F103C8T6工程模板
  * @hardware     : STM32F103C8T6最小系统板的板上LED
  * @software     : Keil MDK + 标准外设库，采用库函数直接控制GPIO口电平
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                        	//定义结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);       	//使能GPIO端口时钟
	
	//下面三个参数的书写，先跳转定义，再Ctrl+F查找这些参数有什么值
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//选择输出模式为推免输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;						//选择13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速度
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);							//第二个参数是结构体的地址
	
  //GPIO_SetBits(GPIOC, GPIO_Pin_13);								//将13号引脚设置为高电平
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);								//将13号引脚设置为低电平
	while(1)
	{
		
	}
}
