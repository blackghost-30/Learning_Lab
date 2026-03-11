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
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;               		// PSC预分频器的值，与AAR和CCR决定PWM的输出频率和占空比
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;					// 分频系数
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 第四步：初始化输出比较单元，带N和IdleState都是高级定时器的内容，可以不用列
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);							// 先给结构体赋一个初值，其他的成员再重新修改
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// 设置输出比较的模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 设置输出比较的极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 设置输出使能
	TIM_OCInitStructure.TIM_Pulse = 50;								// 设置CCR寄存器，与AAR和PSC决定PWM的输出频率和占空比
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);						// 这里选择OC3通道是因为PA2口对应的比较输出通道是OC3
	
	// 第五步：初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);			// 使能GPIOA端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;						// 驱动直流电机用了通道3，所以这里选择初始化PA2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第四步：启动定时器
	TIM_Cmd(TIM2, ENABLE);
	
	/******************************************************************************
    要用AFIO的重映射功能则需要添加第一二句
	若要解除调试功能则添加第一三句
	若要重映射功能的引脚恰好是调试端口则加第一二三句
	若更改了重映射记得要更改初始化的GPIO口
      
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//使能AFIO时钟，AFIO是APB2总线上的外设
	
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);		// 前两个重映射后两个不重映射
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	// 解除JTAG的调试，但是不解除SWD的调试
	  
	******************************************************************************/
}

/**
  * @brief  改变占空比函数
  * @param  Compare 写入CCR寄存器的值
  * @retval 无
  */
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);		// 调用TIM_SetCompare3函数用于更改CCR寄存器的值进而改变PWM的占空比
}


