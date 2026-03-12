#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>						// 为了封装sprintf函数引入头文件

/**
  * @brief  串口初始化函数
  * @param  无
  * @retval 无
  */
void Serial_Init(void)
{
	// 第一步：开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	// USART1是APB2上的外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// USART1的RX和TX引脚对应PA9和PA10，开启GPIOA的时钟
	
	// 第二步：初始化GPIO引脚，此工程只需要数据发送，只初始化TX即可
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//选择复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第三步：初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;											// 波特率，直接写数值即可
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		// 不选择硬件流
	USART_InitStructure.USART_Mode = USART_Mode_Tx;										// 模式
	USART_InitStructure.USART_Parity = USART_Parity_No;									// 是否需要校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;								// 停止位的位数
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;							// 选择字长，这里不需要校验位，所以是8位
	USART_Init(USART1, &USART_InitStructure);
	
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
	USART_SendData(USART1, Byte);		// 调用SendData函数发送数据，将数据写入发送数据寄存器
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);        // 判断发送数据寄存器中的值是否已经移位入移位寄存器中
}

/**
  * @brief  发送一个数组的函数
  * @param  *Array 要发送的数组的地址
  * @param  Length 要发送的数组的长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)	//参数是指向待发送数组的首地址，并指定长度
{
	uint16_t i;						//计数变量
	for (i = 0; i < Length; i ++)	//循环执行，对Array进行遍历
	{
		Serial_SendByte(Array[i]);	//不断发送Array中的元素
	}
}

/**
  * @brief  发送字符串的函数
  * @param  *String 要发送的字符串的地址
  * @retval 无
  */
void Serial_SendString(char *String)	//由于字符串自带结束位，所以不需要长度的参数
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
  * @brief  Printf()函数重封装
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
