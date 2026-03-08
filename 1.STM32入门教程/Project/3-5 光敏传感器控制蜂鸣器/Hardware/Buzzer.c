#include "stm32f10x.h"                  // Device header

/**
  * @brief  蜂鸣器引脚初始化
  * @param  无
  * @retval 无
  */
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		// 使能GPIOB端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;                        // 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            // 定义结构体的模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                  // 选中12号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           // 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      // 初始化端口

	GPIO_SetBits(GPIOB, GPIO_Pin_12);							// 初始化拉高电平防止一上电蜂鸣器就叫
}

/**
  * @brief  启动蜂鸣器函数
  * @param  无
  * @retval 无
  */
void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);		// 低电平启动
}

/**
  * @brief  关闭蜂鸣器函数
  * @param  无
  * @retval 无
  */
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);		//高电平熄灭
}

/**
  * @brief  翻转蜂鸣器函数
  * @param  无
  * @retval 无
  */
void Buzzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)		// 读取蜂鸣器引脚电平进行取反
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
}
