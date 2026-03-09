#include "stm32f10x.h"                  // Device header

/**
  * @brief  片选引脚输出函数，引脚为PA4，软件模拟
  * @param  BitValue 片选引脚输出电平
  * @retval 无
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);    //在SS对应的引脚输出高低电平，表示从机选择
}

/**
  * @brief  SPI初始化函数
  * @param  无
  * @retval 无
  */
void MySPI_Init(void)
{
	// 第一步：开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	// 使能GPIOA端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	// 开启SPI的时钟
	
	// 第二步：初始化GPIO
	// 初始化SS引脚，即PA4
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// 输出引脚配置为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				// 选中4号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化MISO引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			// 输入引脚配置为上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				// 选中6号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 初始化MOSI和SCK引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 输出引脚配置为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;	// 选中5号引脚和7号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// 定义速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第三步：初始化SPI
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;	// 决定SCK时钟的频率，500多KHz
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;							// 与CPOL指定工作模式0
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;								// 与CPHA指定工作模式0
	SPI_InitStructure.SPI_CRCPolynomial = 7;								// CRC校验的多项式，不用理它给个默认值即可
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;						// 8位数据帧
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;		// 选中工作模式，对应的就是SPI的引脚裁剪功能，这里选择的就是双线全双工
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;						// 高位先行
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							// 决定是主机还是从机
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;								// 利用引脚模拟NSS引脚，所以选择软件方式
	SPI_Init(SPI1, &SPI_InitStructure);
	
	// 第四步：使能SPI
	SPI_Cmd(SPI1, ENABLE);
	
	// 第五步：默认给SS输出高电平，默认不选择从机
	MySPI_W_SS(1);
}

/**
  * @brief  起始信号
  * @param  无
  * @retval 无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);		//起始条件为SS置低电平
}

/**
  * @brief  终止信号
  * @param  无
  * @retval 无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);		//终止条件为SS置高电平
}

/**
  * @brief  交换一个字节时序，基于模式0
  * @param  ByteSend 要发送的字节
  * @retval ByteReceive 接收到的字节
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	// 先判断TXE是否置位，即判断是发送缓冲区是否为空，写入数据会自动清除标志位
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET);
	
	// 写入要发送的数据，这里是写入TDR，即发送缓存器
	SPI_I2S_SendData(SPI1, ByteSend);
	
	// 等待RXNE，读数据会清除此标志位
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET);
	
	// 读取DR寄存器的值
	return SPI_I2S_ReceiveData(SPI1);
}















