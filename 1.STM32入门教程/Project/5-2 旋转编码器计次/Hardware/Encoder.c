#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;		// 定义全局计数变量

/**
  * @brief  旋转编码器初始化函数
  * @param  无
  * @retval 无
  */
void Encoder_Init(void)
{
	// 第一步：开启外设的时钟，EXTI和NVIC是不需要开启时钟的，它们的时钟一直开着，不用对它们操作
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	// 第二步：配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 对于外部中断来说，需要选择浮空输入、上拉输入或下拉输入中的一个模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
	
	// 第三步：配置AFIO这里的GPIO_EXTILineConfig本质上就是AFIO_EXTILineConfig
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);		// 执行这个函数后GPIOB0就被选好了，且AFIO输出端固定连接了EXTI的第0个中断线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);		// 执行这个函数后GPIOB1就被选好了，且AFIO输出端固定连接了EXTI的第1个中断线路
	
	// 第四步：配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;			//指定要配置的中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//指定中断线的新状态
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				//指定外部中断源的模式，中断模式或是事件模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;			//指定触发方式
	EXTI_Init(&EXTI_InitStructure);
	
	// 第五步：配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//设置NVIC的分组，且整个芯片分组方式只能用一种
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;					//指定中断通道来开启或关闭，其中EXTI10到EXTI15合并到了一个通道上
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;					//指定中断通道使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;			//指定抢占优先级，根据前面的分组，查表知这个参数的范围是0~3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;					//指定响应优先级，根据前面的分组，查表知这个参数的范围是0~3
	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;					//指定中断通道来开启或关闭，其中EXTI10到EXTI15合并到了一个通道上
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;					//指定中断通道使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;			//指定抢占优先级，根据前面的分组，查表知这个参数的范围是0~3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;					//指定响应优先级，根据前面的分组，查表知这个参数的范围是0~3
	NVIC_Init(&NVIC_InitStruct);
}

/**
  * @brief  返回编码器计数变量的变化量
  * @param  无
  * @retval 无
  */
int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}

/**
  * @brief  中断服务函数
  * @param  无
  * @retval 无
  */
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(EXTI_Line0) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)		// 不要在主函数和中断函数中执行对同一个硬件的操作，可通过变量或标志位来实现在主函数中输出
		{
			Encoder_Count --;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

/**
  * @brief  中断服务函数
  * @param  无
  * @retval 无
  */
void EXTI1_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(EXTI_Line1) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			Encoder_Count ++;
		}		
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
