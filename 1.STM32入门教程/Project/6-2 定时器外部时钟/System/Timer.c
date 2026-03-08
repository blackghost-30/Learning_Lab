#include "stm32f10x.h"                  // Device header

/**
  * @brief  定时器初始化
  * @param  无
  * @retval 无
  */
void Timer_Init(void)
{
	// 第一步：开启RCC时钟，TIM2是APB1总线的外设
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 使用的TIM2的ETR引脚是PA0，所以这里还需要初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第二步：选择时基单元的时钟，这里选择外部时钟
	// 通过ETR的外部时钟模式2配置
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
	
	// 第三步：配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 配置的是滤波器，采样的频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 配置计数器的模式，这里选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1;						// ARR自动重装器的值，当从0到9时产生中断
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;					// PSC预分频器的值，这里没有分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 第四步：使能更新中断，这样就开启了更新中断到NVIC的通路
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);			// 复位之后马上进入1了，需手动清除一下更新中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// 第五步：配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 选择分组二
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;				// TIM2_IRQn就是定时器2在NVIC的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// 直接使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	// 抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	// 第六步：启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  返回计数值
  * @param  无
  * @retval 计数值
  */
uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
}

/**
  * @brief  中断服务函数模板
  * @param  无
  * @retval 无
  */
/*
void TIM2_IRQHandler(void)		// 中断函数名都是固定的，要去启动文件中找
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update == SET))	// 检查中断标志位
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		// 手动清空标志位，防止重复进入中断
	}
}
*/









