#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的蜂鸣器控制工程
  * @brief        : 基于STM32的GPIO口电平设置进行蜂鸣器控制
  * @hardware     : STM32103C8T6 + 蜂鸣器 ，采用GPIOB12端口控制蜂鸣器
  * @software     : Keil MDK + 标准外设库，采用库函数直接控制GPIO口电平
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// 用PB12号口，开启PB的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// 推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				// 选择PB12号口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					// 把GPIO引脚配置写入配置寄存器
	
	while (1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);		// 低电平蜂鸣器响
		Delay_ms(500);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);		// 高电平蜂鸣器停
		Delay_ms(500);		
	}
}

/**
  ******************************************************************************
  * 使用库函数的方法
  * @方法1			: 打开.h文件最后，先看一下都有什么函数，再跳转定义查看参数定义
  * @方法2			: 查看库函数用户手册，一个个学习
  * @方法3			: 百度搜索参考其他人的代码
  ******************************************************************************
  */
