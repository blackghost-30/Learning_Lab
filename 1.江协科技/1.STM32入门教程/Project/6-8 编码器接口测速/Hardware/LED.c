#include "stm32f10x.h"                  // Device header
#include "LED.h"

/**
  * @brief  LED引脚(GPIOA1和GPIOA2)初始化
  * @param  无
  * @retval 无
  */
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;						// 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            // 定义结构体的模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;      // 选中1号引脚和2号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           // 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      // 初始化端口

	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);               // 前面初始化后默认是低电平，这条语句可以把端口设置为高电平
}

/**
  * @brief  点亮LED1灯，即拉底GPIOA1的引脚电平
  * @param  无
  * @retval 无
  */
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);		// 低电平点亮
}

/**
  * @brief  熄灭LED1灯，即拉高GPIOA1的引脚电平
  * @param  无
  * @retval 无
  */
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1);       // 高电平熄灭
}

/**
  * @brief  反转LED1端口的电平
  * @param  无
  * @retval 无
  */
void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)		// 读取PA1引脚的输出值，进而取反
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}

/**
  * @brief  点亮LED2灯，即拉底GPIOA2的引脚电平
  * @param  无
  * @retval 无
  */
void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

/**
  * @brief  熄灭LED2灯，即拉高GPIOA2的引脚电平
  * @param  无
  * @retval 无
  */
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_2);
}

/**
  * @brief  反转LED1端口的电平
  * @param  无
  * @retval 无
  */
void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)     // 读取PA2引脚的输出值，进而取反
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}
