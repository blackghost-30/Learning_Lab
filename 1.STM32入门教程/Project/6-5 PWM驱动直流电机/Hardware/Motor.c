#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * @brief  电机初始化函数
  * @param  无
  * @retval 无
  */
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			// 定义结构体的模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;		// 选中4号引脚和5号引脚，来控制电机的转向
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_Init();
}

/**
  * @brief  设置电机速度的函数
  * @param  无
  * @retval 无
  */
void Motor_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);		// 这里设置PA4为高、PA5为低时是正转的方向
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);		// 这里设置PA4为低、PA5为高时是反转的方向
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompare3(-Speed);				// 因为这里Speed是负数，所以需要取负
	}
}





