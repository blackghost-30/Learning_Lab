#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的流水灯工程
  * @brief        : 基于STM32的GPIO口电平设置进行流水灯控制
  * @hardware     : STM32103C8T6 + LED，采用GPIOA的8个端口控制8个LED
  * @software     : Keil MDK + 标准外设库，采用库函数直接控制GPIO口电平
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 开启时钟，可用|选中多个端口
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        // 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;             // 可通过按位或|运算选中所有的引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                  // 把GPIO引脚配置写入配置寄存器
	
	GPIO_SetBits(GPIOA, GPIO_Pin_0);						// 上电瞬间先将GPIO口设置为高电平
	
	while (1)
	{
		// GPIO_Write()函数对16个端口进行配置
		GPIO_Write(GPIOA, ~0x0001);		// 0000 0000 0000 0001
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0002);     // 0000 0000 0000 0010
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0004);     // 0000 0000 0000 0100
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0008);     // 0000 0000 0000 1000
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0010);     // 0000 0000 0001 0000
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0020);     // 0000 0000 0010 0000
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0040);     // 0000 0000 0100 0000
		Delay_ms (500);
		GPIO_Write(GPIOA, ~0x0080);     // 0000 0000 1000 0000
		Delay_ms (500);
	}
}
