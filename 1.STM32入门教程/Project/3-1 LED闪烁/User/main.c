#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的LED闪烁工程
  * @brief        : 基于STM32的GPIO口电平设置进行LED闪烁控制
  * @hardware     : STM32103C8T6 + LED，采用GPIOA0端口控制LED
  * @software     : Keil MDK + 标准外设库，采用库函数直接控制GPIO口电平
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIO时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //推挽输出，两者均具有驱动能力，开漏输出只有低电平有
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;               //指定引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       //指定速度
	GPIO_Init(GPIOA, &GPIO_InitStructure);                  //把GPIO引脚配置写入配置寄存器
	
	while (1)
	{
		//第一种方法：用GPIO_WriteBit()进行位设置
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);		//设置PA0端口为低电平
		Delay_ms(1000);
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);			//设置PA0端口为高电平
		Delay_ms(1000);
		
		//第二种方法：用ResetBits()进行位设置
//		GPIO_ResetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为低电平
//		Delay_ms(500);
//		GPIO_SetBits(GPIOA, GPIO_Pin_0);					//将PA0引脚设置为高电平
//		Delay_ms(500);
		
		//第三种方法：用WriteBit()函数进行0、1置位
//		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)0);		//将PA0引脚设置为低电平，这里的BitsAction是为了将0转变为枚举类型（强制类型转换）
//		Delay_ms(500);										//延时500ms
//		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)1);		//将PA0引脚设置为高电平这里的BitAction同理
//		Delay_ms(500);										//延时500ms
	}
}
