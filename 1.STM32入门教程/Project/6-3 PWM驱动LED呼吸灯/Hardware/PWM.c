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
	TIM_InternalClockConfig(TIM2);		// 上电后默认的是内部时钟，这一行也可不写
	
	// 第三步：配置时基单元，这里不需要更新中断，所以不需要NVIC的初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 滤波器的设置，决定采样的频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 配置计数器的模式，这里选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;						// ARR自动重装器的值，与PSC和CCR决定PWM的输出频率和占空比
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;					// PSC预分频器的值，与AAR和CCR决定PWM的输出频率和占空比
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 第四步：初始化输出比较单元，带N和IdleState的是高级定时器的内容，可以不用列
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);							// 先给结构体赋一个初值，其他的成员再重新修改，兼容高级定时器
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				// 设置输出比较的模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		// 设置输出比较的极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	// 设置输出使能
	TIM_OCInitStructure.TIM_Pulse = 50;								// 设置CCR寄存器，与AAR和PSC决定PWM的输出频率和占空比
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);						// 这里选择OC1通道是因为PA0口对应的比较输出通道是OC1
	
	// 第五步：初始化GPIO，即引脚的复用功能和重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 使能GPIOA端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 模式需要选择复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				// 选中0号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 初始化端口
	
	//第四步：启动定时器
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
  * @brief  更改CCR寄存器的值的函数，可用于改变占空比
  * @param  Compare 占空比
  * @retval 无
  */
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);		// TIM_SetCompare1函数更改CCR寄存器的值进而改变PWM的占空比
}


