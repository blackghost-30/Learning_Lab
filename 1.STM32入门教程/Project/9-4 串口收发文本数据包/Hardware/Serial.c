#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>						// 为了封装sprintf函数引入头文件

// 定义缓冲区数组用于存放数据
char Serial_RxPacket[100];
uint8_t Serial_RxFlag;			// 定义自己的标志位，若收到一个数据包就置RxFlag

void Serial_Init(void)
{
	// 第一步：开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);		// USART1是APB2上的外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// USART1的RX和TX引脚对应PA9和PA10，开启GPIOA的时钟
	
	// 第二步：初始化GPIO引脚，这个代码需要数据发送和数据接收，初始化TX和RX
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				// 选择复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;					// 接收和发送分别对应PA9和PA10
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				// 选择上拉输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;					// 接收和发送分别对应PA9和PA10
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第三步：初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;											// 波特率，直接写数值，Init函数会解决分频问题
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// 不选择硬件流
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;						// 模式，这里需要或上两者
	USART_InitStructure.USART_Parity = USART_Parity_No;									// 是否需要校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								// 停止位的位数
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							// 选择字长，这里不需要校验位，8位
	USART_Init(USART1, &USART_InitStructure);
	
	// 若用中断的方法接收，则需要开启中断并配置NVIC，即只要RXNE置1就会产生通向NVIC的中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		// 选择RXNE的中断，开启RXNE标志位到NVIC的输出
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// NVIC分组
	
	NVIC_InitTypeDef NVIC_InitStructure;						// 初始化NVIC的USART1的通道
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			// 选择通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				// 使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	// 优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			// 优先级
	NVIC_Init(&NVIC_InitStructure);
	
	// 第四步：开关控制开启USART
	USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  发送一个字节函数
  * @param  Byte 要发送的字节内容
  * @retval 无
  */
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);		// 调用SendData函数，将数据写入发送数据寄存器
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		// 判断发送数据寄存器中的值是否已经移位入移位寄存器中
}

/**
  * @brief  发送一个数组的函数
  * @param  *Array 要发送的数组的地址
  * @param  Length 要发送的数组的长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)		// 参数是指向待发送数组的首地址，并指定长度
{
	uint16_t i;
	for (i = 0; i < Length; i ++)	// 循环执行，对Array进行遍历
	{
		Serial_SendByte(Array[i]);	// 不断发送Array中的元素
	}
}

/**
  * @brief  发送字符串的函数
  * @param  *String 要发送的字符串的地址
  * @retval 无
  */
void Serial_SendString(char *String)		// 由于字符串自带结束位，所以不需要长度的参数
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

/**
  * @brief  次方函数
  * @param  x 底数
  * @param  y 指数
  * @retval 无
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  发送数字函数，以字符的形式显示
  * @param  Number 数字
  * @param  Length 长度
  * @retval 无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i ++)
	{
		// 参数以十进制从高位到低位依次发送，还要加上偏移
		Serial_SendByte(Number / Serial_Pow(10, Length -i -1) % 10 + '0');
	}
}

/**
  * @brief  重定向函数
  * @param  无
  * @retval 无
  */
int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

/**
  * @brief  sprintf()函数重封装
  * @param  无
  * @retval 无
  */
void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}

/**
  * @brief  状态机写接收数据包中断服务函数，电脑端发送数据时记得加上\n
  * @param  无
  * @retval 无
  */
void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;			// 定义一个状态变量
	static uint8_t pRxPacket = 0;		// 定义变量计数接收到的数据量
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if (RxState == 0)		// 进入等待包头的程序
		{
			if (RxState == '@' && Serial_RxFlag == 0)		// 若接收到包头并且已经完成当次接收，才将状态置1
			{
				RxState = 1;
				pRxPacket = 0;	// 置0为下一次接收数据做准备
			}
		}
		
		else if (RxState == 1)		// 进入接收数据的程序
		{
			if (RxData == '\r')		// 需要首先判断是不是接收到包尾，因为这里是可变包长
			{
				RxState = 2;
			}
			else
			{
				Serial_RxPacket[pRxPacket] = RxData;		// 将数据存入数组
				pRxPacket ++;		// 计数++				
			}
		}
		
		else if (RxState == 2)		// 进入等待包尾的程序
		{
			if (RxData == '\n')		// 这里只需要检测是不是等于第二个包尾，因为第一个包尾在前面检测了
			{
				RxState = 0;
				Serial_RxPacket[pRxPacket] = '\0';		// 这里添加结束位，即字符串的结束位			
				Serial_RxFlag = 1;						// 置自己的标志位，表示收到数据

			}
		}
		// 若读取了DR寄存器会自动清除标志位，但这里手动清除一下也没关系
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
