#include "stm32f10x.h"                  // Device header

/**
  ******************************************************************************
  * @brief        : 这是软件SPI应用层封装
  * @brief        : 由于SPI的速度很快所以不需要加延时
  ******************************************************************************
  */

/**
  * @brief  片选引脚输出函数，引脚为PA4
  * @param  BitValue 片选引脚输出电平
  * @retval 无
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);		// 在SS对应的引脚输出高低电平，表示从机选择
}

/**
  * @brief  时钟线输出函数，引脚为PA5
  * @param  BitValue 时钟线电平
  * @retval 无
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

/**
  * @brief  主机输出函数，引脚为PA7
  * @param  BitValue 输出线电平
  * @retval 无
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

/**
  * @brief  主机输入函数，引脚为PA6
  * @param  无
  * @retval 输入的电平数据
  */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);		// 直接读MISO的对应引脚电平
}

/**
  * @brief  SPI初始化函数
  * @param  无
  * @retval 无
  */
void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 使能GPIOA端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;									// 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;						// 输出引脚配置为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;		// 选中4号引脚和5号引脚和7号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;						// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);									// 初始化端口
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 输入引脚配置为上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				// 选中1号引脚和2号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// 初始化端口
	
	// 置一下初始化后引脚的默认电平，MOSI没有明确规定，可以不管，MISO是输入引脚所以不需要置电平
	MySPI_W_SS(1);		// 初始化后SS的引脚应为高电平，默认不选择从机
	MySPI_W_SCK(0);		// SPI模式0，对应为低电平
}

/**
  * @brief  起始信号
  * @param  无
  * @retval 无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);		// 起始条件为SS置低电平
}

/**
  * @brief  终止信号
  * @param  无
  * @retval 无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);		// 终止条件为SS置高电平
}

/**
  * @brief  交换一个字节时序，基于模式0
  * @param  ByteSend 要发送的字节
  * @retval ByteReceive 接收到的字节
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;		// 定义一个i用于计数，ByteReceive用于返回接收值
	
	for (i = 0; i < 8; i ++)			// 循环发送一个字节
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));	// SS下降沿将主机数据移出到MOSI，这里的移位操作本质是掩码
		MySPI_W_SCK(1);							// 产生上升沿读数据
		if (MySPI_R_MISO() == 1)				// 读取MISO线上的数据，若为1则写入ByteReceive的最高位
		{
			ByteReceive |= (0x80 >> i);
		}
		MySPI_W_SCK(0);							// 产生下降沿移出数据
	}
	return ByteReceive;
}


