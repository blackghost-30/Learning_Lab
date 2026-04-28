#include "stm32f10x.h"                  // Device header

/**
  * @brief  CAN外设初始化函数
  * @param  无
  * @retval 无
  */
void MyCAN_Init(void)
{
	/* 初始化第一步：开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	/* 初始化第二步：初始化GPIO口 */
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* 初始化第三步：CAN外设的初始化 */
	CAN_InitTypeDef CAN_InitStrcuture;
	
	CAN_InitStrcuture.CAN_Mode = CAN_Mode_Normal;	// 选择测试模式，给正常模式
	CAN_InitStrcuture.CAN_Prescaler = 48;
	CAN_InitStrcuture.CAN_BS1 = CAN_BS1_2tq;	// 函数内部自动减1，给参数时不需减1
	CAN_InitStrcuture.CAN_BS2 = CAN_BS2_3tq;	// 波特率 = 36M / 48 / (1 + 2 + 3) = 125K
	CAN_InitStrcuture.CAN_SJW = CAN_SJW_2tq;
	CAN_InitStrcuture.CAN_NART = DISABLE;		// 不自动重装配置位
	CAN_InitStrcuture.CAN_TXFP = DISABLE;		// 发送邮箱优先级，选择ID号
	CAN_InitStrcuture.CAN_RFLM = DISABLE;		// FIFO锁定
	CAN_InitStrcuture.CAN_AWUM = DISABLE;		// 自动唤醒
	CAN_InitStrcuture.CAN_TTCM = DISABLE;		// 时间触发通信
	CAN_InitStrcuture.CAN_ABOM = DISABLE;		// 离线自动恢复
	
	CAN_Init(CAN1, &CAN_InitStrcuture);
	
	/* 初始化第四步：配置过滤器 */
	CAN_FilterInitTypeDef CAN_FilterInitStrcuture;
	
	CAN_FilterInitStrcuture.CAN_FilterNumber = 0;							// 初始化的过滤器
	CAN_FilterInitStrcuture.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStrcuture.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStrcuture.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStrcuture.CAN_FilterMaskIdLow = 0x0000;					// 32位屏蔽模式的全通
	CAN_FilterInitStrcuture.CAN_FilterScale = CAN_FilterScale_32bit;		// 位宽
	CAN_FilterInitStrcuture.CAN_FilterMode = CAN_FilterMode_IdMask;			// 屏蔽模式
	CAN_FilterInitStrcuture.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;	// 关联，数据进入FIFO0
	CAN_FilterInitStrcuture.CAN_FilterActivation = ENABLE;					// 激活，打开过滤器
	
	CAN_FilterInit(&CAN_FilterInitStrcuture);
}

/**
  * @brief  CAN发送报文函数
  * @param  TxMessage	要发送报文的结构体
  * @retval 无
  */
void MyCAN_Transmit(CanTxMsg *TxMessage)
{
	/* 等待报文发送完成 */
	uint8_t TransmitMailbox =  CAN_Transmit(CAN1, TxMessage);
	
	uint32_t Timeout = 0;
	while (CAN_TransmitStatus(CAN1, TransmitMailbox) != CAN_TxStatus_Ok)
	{
		Timeout ++;
		if (Timeout > 100000)
		{
			break;
		}
	}
}

/**
  * @brief  获取FIFO状态函数
  * @param  无
  * @retval 1 / 0
  */
uint8_t MyCAN_ReceiveFlag(void)
{
	if (CAN_MessagePending(CAN1, CAN_FIFO0) > 0)
	{
		return 1;
	}
	return 0;
}

/**
  * @brief  CAN接收报文函数
  * @param  RxMessage	接收报文结构体
  * @retval 无
  */
void MyCAN_Receive(CanRxMsg *RxMessage)
{
	CAN_Receive(CAN1, CAN_FIFO0, RxMessage);
}
