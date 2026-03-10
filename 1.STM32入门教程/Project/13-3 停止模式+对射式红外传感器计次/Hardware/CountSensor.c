#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;				// 全局变量，返回给主函数

/**
  * @brief  红外传感器初始化，包括初始化引脚和配置外部中断
  * @param  无
  * @retval 无
  */
void CountSensor_Init(void)
{
	// 第一步：开启外设的时钟，EXTI和NVIC不需要开启时钟的，它们的时钟一直开着，所以不用对它们操作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// 第二步：配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   	// 对于外部中断来说，需要选择浮空输入、上拉输入或下拉输入中的一个模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
	// 第三步：配置AFIO，注意AFIO的库文件是和GPIO放在一块的
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);   	// 执行这个函数后GPIOB14就被选好了，且AFIO输出端固定连接了EXTI的第十四个中断线路
	
	// 第四步：配置EXTI，即将EXTI的第14个线路配置为中断模式，下降沿触发，并开启中断
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;					// 指定要配置的中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					// 指定中断线的新状态
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			// 指定外部中断源的模式，中断模式或是事件模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		// 指定触发方式
	EXTI_Init(&EXTI_InitStructure);
	
	// 第五步：配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				// 设置NVIC的分组，且整个芯片分组方式只能用一种
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;			// 指定中断通道来开启或关闭，其中EXTI10到EXTI15合并到了一个通道上
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;				// 指定中断通道使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;		// 指定抢占优先级，根据前面的分组，查表知这个参数的范围是0~3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;				// 指定响应优先级，根据前面的分组，查表知这个参数的范围是0~3
	NVIC_Init(&NVIC_InitStruct);
}

/**
  * @brief  封装计数值返回函数
  * @param  无
  * @retval 计数值
  */
uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

/**
  * @brief  中断服务函数
  * @param  无
  * @retval 无
  */
void EXTI15_10_IRQHandler(void)						// 中断函数不需要在.h文件中声明，它是不需要调用的
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)		// 该通道EXTI15~10都可以进来，要先判断是不是14号的中断源
	{
		CountSensor_Count ++;						// 执行操作
		EXTI_ClearITPendingBit(EXTI_Line14);		// 中断程序结束后清除中断标志位的函数，防止重复进入中断
	}
}


