#include "stm32f10x.h"                  // Device header

/**
  * @brief  PWM初始化函数
  * @param  无
  * @retval 无
  */
void PWM_Init(void)
{
	// 第一步：开启RCC时钟，TIM2是APB1总线的外设
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 第二步：选择时基单元的时钟，选择内部时钟
	TIM_InternalClockConfig(TIM2);		// 但是上电后默认的是内部时钟，这一行也可不写
	
	// 第三步：配置时基单元，这里不需要更新中断，所以不需要NVIC的初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 滤波器的设置，采样的频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 数配置计数器的模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;					// ARR自动重装器的值，与PSC和CCR决定PWM的输出频率和占空比
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;					// PSC预分频器的值，与AAR和CCR决定PWM的输出频率和占空比
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	/******************************************************************************
    若用高级定时器输出四路PWM，需要所有结构体的成员都赋初始值，否则出错
	第一种方法：给所有结构体的成员都赋值；
	第二种方法：给结构体赋初值，再对一些相关要修改的结构体的成员修改
	其中赋初值的函数为TIM_OCStructInit()
	******************************************************************************/
	// 第四步：初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);							// 先给结构体赋一个初值，其他的成员再重新修改
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// 设置输出比较的模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 设置输出比较的极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 设置输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;								// 设置CCR寄存器，与AAR和PSC决定PWM的输出频率和占空比，
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);						// PA1口对应的比较输出通道是OC2
	
	/******************************************************************************
    外设的引脚复用在GPIO口上，当用到某个复用功能的GPIO时就需要开启该GPIO的时钟
	******************************************************************************/	
	// 第五步：初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;						// 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				// 复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;					// 初始化PA1，因为使用的是通道二
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第四步：启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  改变占空比函数
  * @param  Compare 写入CCR寄存器的值
  * @retval 无
  */
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);			// 调用TIM_SetCompare1函数用于更改CCR寄存器的值进而改变PWM的占空比
}


