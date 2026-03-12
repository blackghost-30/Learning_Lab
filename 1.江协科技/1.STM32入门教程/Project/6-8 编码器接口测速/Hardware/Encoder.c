#include "stm32f10x.h"                  // Device header

/**
  * @brief  编码器初始化函数
  * @param  无
  * @retval 无
  */
void Encoder_Init(void)
{
	// 第一步：开启RCC时钟，TIM3是APB1总线的外设，这里因为需要用TIM2输出PWM，所以输入捕获使用TIM3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	// 第二步：配置时基单元，因为这里不需要更新中断，所以不需要NVIC的初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// 滤波器的设置，采样的频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 配置计数器的模式，这里选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;					// ARR自动重装器的值，防止溢出，这里给最大
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;					// 这里不需要分频
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;				// 重复计数器的值，高级定时器才有，直接给0
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	// 第三步：初始化GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA端口时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				// 输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;		// 这里选择TIM3的通道1和通道2，对应的引脚是PA6和PA7，所以需要选中PA6和PA7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);						// 初始化端口
	
	// 第四步：初始化捕获单元，这里只使用了滤波器和极性选择
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);		// 这里有些参数没有用到，需要用该函数统一赋初值
	
	// 初始化通道1
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;				// 选择配置哪个通道，这里选择通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							// 滤波器，但是不会更改信号的频率
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		// 选择极性，但是这里不代表上升沿有效，而是指高低电平不反转
	TIM_ICInit(TIM3, &TIM_ICInitStructure);							// 初始化捕获单元
	// 初始化通道2
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;				// 选择配置哪个通道，这里选择通道2
	TIM_ICInitStructure.TIM_ICFilter = 0xF;							// 滤波器，但是不会更改信号的频率
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		// 选择极性，但是这里不代表上升沿有效，而是指高低电平不反转
	TIM_ICInit(TIM3, &TIM_ICInitStructure);							// 初始化捕获单元
	
	// 第五步：配置编码器接口
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);     // 这里后面的两个参数和前面设置的Rising参数一样
	
	// 第六步：使能计数器
	TIM_Cmd(TIM3, ENABLE);
}

/**
  * @brief  读取速度的函数，用int变量显示负数，利用补码特性
  * @param  无
  * @retval CNT的值
  */
int16_t Encoder_Get(void)
{
	int16_t Temp;					// 定义临时存放变量
	Temp = TIM_GetCounter(TIM3);	// 获取当前CNT的值
	TIM_SetCounter(TIM3, 0);		// 将CNT的值清零
	return Temp;					// 返回CNT的值
}
