#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * @brief  封装SCL线置位的函数
  * @param  BitValue 要置位的数据
  * @retval 无
  */
void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);
	Delay_us(10);					// 延迟10us，防止速度过快
}

/**
  * @brief  封装SDA线置位的函数
  * @param  BitValue 要置位的数据
  * @retval 无
  */
void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
	Delay_us(10);					// 延迟10us，防止速度过快
}

/**
  * @brief  封装读SDA线数据的函数
  * @param  无
  * @retval 读取的电平值
  */
uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);		// 读GPIO口的数据
	Delay_us(10);					// 延迟10us，防止速度过快
	return BitValue;
}

/**
  * @brief  软件I2C初始化函数
  * @param  无
  * @retval 无
  */
void MyI2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		// 使能GPIOB端口时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;						// 定义结构体
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;			// 开漏输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;    // 选中10号引脚和11号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           // 定义速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                      // 初始化端口

	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);				// 把端口设置为高电平，对应I2C的空闲状态，此时总线是释放状态
}

/**
  * @brief  起始条件
  * @param  无
  * @retval 无
  */
void MyI2C_Start(void)
{
	// 起始条件：先释放总线，再先将SCL拉低，然后将SDA拉低，注意这里需要兼容重复起始条件的时序
	MyI2C_W_SDA(1);			// 先释放SDA总线，再释放SCL总线，才能防止被认为是终止信号
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);			// 先拉低SDA总线
	MyI2C_W_SCL(0);			// 再拉低SCL总线
}

/**
  * @brief  终止条件
  * @param  无
  * @retval 无
  */
void MyI2C_Stop(void)
{
	// 先拉低SDA，再释放SCL和SDA
	// 先拉底SDA是因为终止时序开始时SDA不一定是低电平，所以为了确保之后释放SDA能产生上升沿，先将SDA拉低
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

/**
  * @brief  发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void MyI2c_SendByte(uint8_t Byte)
{
	uint8_t i;			// 定义迭代变量i
	
	for (i = 0; i < 8; i ++)                    // 迭代8次，发送一个字节
	{
		// 虽然传入的不是0/1，但是MyI2C_W_SDA()函数内部进行了枚举类型转换
		MyI2C_W_SDA(Byte & (0x80 >> i));		// 取出数据的位，通过移位操作实现不同位的读取
		MyI2C_W_SCL(1);							// 放完数据后释放SCL，这时候从机就会读取SDA的值
		MyI2C_W_SCL(0);							// 再拉低SCL，进入次高位的发送
	}
}

/**
  * @brief  接收一个字节
  * @param  无
  * @retval 接收到的字节数据
  */
uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;				// 定义迭代变量和数据存储变量
	MyI2C_W_SDA(1);						// 主机先释放SDA，让从机写数据
	for (i = 0; i < 8; i ++)			// 迭代八次，接收一个字节
	{
		MyI2C_W_SCL(1);					// 主机释放SCL，此时即可读数据了
		if (MyI2C_R_SDA() == 1)
		{
			Byte |= (0x80 >> i);		// 通过或的操作写入Byte的最高位
		}
		MyI2C_W_SCL(0);					// 读完数据后再将SCL拉低，这时从机就会把下一位数据放到SDA上
	}
	return Byte;
}

/**
  * @brief  发送应答，即发1位
  * @param  AckBit 要发送的应答位
  * @retval 无
  */
void MyI2c_SendAck(uint8_t AckBit)
{
	// 函数进来时SCL是低电平
	MyI2C_W_SDA(AckBit);		// 此时主机将应答位放上SDA上
	MyI2C_W_SCL(1);				// 放完数据后释放SCL，这时候从机就会读取应答
	MyI2C_W_SCL(0);				// 再拉低SCL，进入下一个单元
}

/**
  * @brief  接收应答，即收1位
  * @param  无
  * @retval 应答位数据
  */
uint8_t MyI2C_ReceiveAck(void)
{
	// 函数进来时SCL为低电平
	uint8_t AckBit;
	MyI2C_W_SDA(1);				// 主机先释放SDA，防止干扰从机，让从机写数据
	MyI2C_W_SCL(1);				// 主机释放SCL，此时即可读数据了
	AckBit = MyI2C_R_SDA();		// 直接将读到的值给AckBit
	MyI2C_W_SCL(0);				// 读完数据后再将SCL拉低，这时从机就会把下一位数据放到SDA上
	return AckBit;
}
