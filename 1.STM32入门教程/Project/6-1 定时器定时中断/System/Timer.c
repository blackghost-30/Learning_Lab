#include "stm32f10x.h"                  // Device header
#include "Timer.h"

/**
  * @brief  定时器初始化
  * @param  无
  * @retval 无
  */
void Timer_Init(void)
{
	// 第一步：开启RCC时钟，TIM2是APB1总线的外设
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 第二步：选择时基单元的时钟，选择内部时钟
	TIM_InternalClockConfig(TIM2);		// 上电后默认的是内部时钟，这一行也可不写
	
	// 第三步：配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 配置滤波器的设置，采样的频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 配置计数器的模式，这里选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;					// ARR自动重装器的值，在10K频率下计10000个数就是1s的时间
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;					// PSC预分频器的值，这里是对72M进行7200分频，得到10K计数频率
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	// 第四步：使能更新中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);			// 复位之后马上进入1了，需手动清除一下更新中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	// 第五步：配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);			// 选择分组二
	
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









