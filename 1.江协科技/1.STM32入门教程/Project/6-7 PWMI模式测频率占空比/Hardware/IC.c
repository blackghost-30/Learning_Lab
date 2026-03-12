#include "stm32f10x.h"                  // Device header

/**
  * @brief  输入捕获初始化函数
  * @param  无
  * @retval 无
  */
void IC_Init(void)
{
	// 第一步：开启RCC时钟，TIM3是APB1总线的外设
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	// 第二步：配置时基单元，因为这里不需要更新中断，所以不需要NVIC的初始化
	TIM_InternalClockConfig(TIM3);		//选择内部时钟，且是TIM3
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 滤波器的设置，采样的频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 配置计数器的模式，这里选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;					// ARR自动重装器的值，防止溢出，这里给最大
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;					// PSC预分频器的值，这个参数决定了基准频率，这里给1MHz
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	// 第三步：初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA端口时钟
	GPIO_InitTypeDef GPIO_InitStructure;						// 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				// 输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;					// 这里选择TIM3的通道1，对应的引脚是PA6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第四步：初始化捕获单元，每一个结构体成员对应电路的一个结构
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;					// 选择配置哪个通道，这里选择通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;								// 滤波器，但是不会更改信号的频率
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;			// 选择极性，选择上升沿触发
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;				// 选择分频器，这里选择不分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;		// 这里选择通道，选择直连通道
	TIM_ICInit(TIM3, &TIM_ICInitStructure);								// 初始化捕获单元
	
	// 第五步：配置TRGI的触发源为TI1FP1以设置从模式用于自动清零CNT
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);				// 选择触发源为TF1FP1
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);				// 选择从模式为Reset
	
	// 第六步：使能计数器以启动定时器
	TIM_Cmd(TIM3, ENABLE);
}

/**
  * @brief  获取频率函数
  * @param  无
  * @retval 返回频率
  */
uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM3) + 1);		// 1000000对应的是经过PSC分频后的基准频率，再调用函数即可读取CCR的值
}

/**
  * @brief  获取占空比函数
  * @param  无
  * @retval 返回频率
  */
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);     // 乘100转换为百分比
}
