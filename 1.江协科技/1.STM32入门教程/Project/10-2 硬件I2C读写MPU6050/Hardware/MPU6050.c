#include "stm32f10x.h"            // Device header
#include "MPU6050_Reg.h"          //将宏定义6050寄存器的头文件加上

#define MPU6050_ADDRESS       0xD0		//宏定义MPU6050的地址

/**
  * @brief  封装CheckEvent函数，用于改进超时的问题，将后面全部的等待时间函数改为该函数
  * @param  I2Cx 指定是哪个I2C外设
  * @param  I2C_EVENT 指定是等待那个事件
  * @retval 无
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t Timeout;				// 用于计数超时
	Timeout = 10000;
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
	{
		Timeout --;
		if (Timeout == 0)
		{
			break;					// 结束函数
		}
	}
}

/**
  * @brief  封装指定地址写寄存器的函数
  * @param  RegAddress 寄存器地址
  * @param  Data 要写入寄存器的数据
  * @retval 无
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	// 产生起始信号，替换软件的Start函数
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					// 等待EV5事件，表示产生起始条件成功
	
	// 发送从机地址
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	// 等待EV6事件，表示发送地址成功
	
	// 发送地址数据
	I2C_SendData(I2C2, RegAddress);			// 这里发送寄存器地址
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);			//等待EV8事件，表示移位寄存器中字节开始发送，可以往数据寄存器中写入值了
	
	// 发送数据
	I2C_SendData(I2C2, Data);				//发送数据
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//等待EV8_2事件，表示字节发送完毕
	
	// 发送终止条件
	I2C_GenerateSTOP(I2C2, ENABLE);
}

/**
  * @brief  封装指定地址读的函数
  * @param  RegAddress 寄存器地址
  * @retval 无
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;

	// 下面的部分是发送数据的前面一部分，即产生起始条件+指定地址
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	
	I2C_SendData(I2C2, RegAddress);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	
	// 生成重复起始条件
	I2C_GenerateSTART(I2C2, ENABLE);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);				// 等待EV5事件
	
	// 发送地址，这里改参数为Receiver，函数内部会自动将最低位置为1，表示读
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);	// 等待EV6事件，但是这个EV6事件和发送的EV6事件不是同一个事件
	
	// 读取数据
	/**
	 ******************************************************************************
	 若读取多个字节，直接等待EV7事件，读取DR，即可收到数据；
	 在接收最后一个字节之前，即EV7_1事件，需要提前将ACK置零，STOP置1；
	 若读取一个字节，则需在EV6事件之后立刻ACK置零，STOP置1，否则时序会多一个字节；
	 若需要多字节只需要将后面四行套循环；
     ******************************************************************************
     */
	I2C_AcknowledgeConfig(I2C2, DISABLE);				// 直接配置ACK位，将其置零
	I2C_GenerateSTOP(I2C2, ENABLE);						// 配置停止位
	
	while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);	// 等待EV7事件，等EV7事件产生后，一个字节的数据就在DR里面了
	Data = I2C_ReceiveData(I2C2);
	
	//将应答位重置为1，方便后面接收多字节的程序改动
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	
	return Data;
}

/**
  * @brief  初始化函数
  * @param  无
  * @retval 无
  */
void MPU6050_Init(void)
{
	// 初始化硬件I2C，替换之前的软件I2C初始化
	// 第一步：开启I2C和GPIO的时钟，I2C2是APB1上的外设
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//第二步：将PB10和PB11都初始化为复用开漏模式
	GPIO_InitTypeDef GPIO_InitStructure;						// 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;				// 定义结构体的模式为复用开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;	// 选中10号引脚和11号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			// 定义速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);						// 初始化端口
	
	// 第三步：初始化I2C2外设
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;	
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;			// 占空比参数，只有在高速状态下才有用
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;					// 接收完一位之后是否给应答位
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;		// STM32作为从机可以响应多少位地址
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;										// 指定自身地址
	I2C_Init(I2C2, &I2C_InitStructure);
	
	// 第四步：使能I2C
	I2C_Cmd(I2C2, ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);			// 配置电源管理寄存器1，这里解除其睡眠状态，并选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);			// 配置电源管理寄存器2，将所有位设置为不待机，即6个轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);			// 配置采样率分频，这里给10分频
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);				// MPU6050的配置寄存器，滤波参数给最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);		// 选择最大量程，16g，最大参数为32768，通过数据除以32768再乘以量程即为真是的加速度值
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);		// 加速度计配置寄存器，选择最大量程，同理上面
}

/**
  * @brief  获取芯片ID的函数
  * @param  无
  * @retval 返回ID号
  */
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

/**
  * @brief  读取多个数据寄存器的值的函数
  * @param  6个数组地址
  * @retval 无直接返回值，通过地址形式返回多个返回值
  */
void MPU6050_GetData(int16_t *Accx, int16_t *Accy, int16_t *Accz,
					 int16_t *Gyrox, int16_t *Gyroy, int16_t *Gyroz)
{
	// 前三部分用于读取加速度计的XYZ轴的数据
	uint8_t DataH, DataL;								// 定义变量存放数据
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);		// 读取加速度寄存器的高8位
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);		// 读取加速度寄存器的低8位
	*Accx = (DataH << 8) | DataL;						// 操作获得加速度计X轴的16位数据，并通过指针返回回去
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);		// 读取加速度寄存器的高8位
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);		// 读取加速度寄存器的低8位
	*Accy = (DataH << 8) | DataL;						// 操作获得加速度计Y轴的16位数据，并通过指针返回回去
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);		// 读取加速度寄存器的高8位
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);		// 读取加速度寄存器的低8位
	*Accz = (DataH << 8) | DataL;						// 操作获得加速度计Z轴的16位数据，并通过指针返回回去	
	
	// 这三部分用于读取陀螺仪的XYZ轴的数据
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);		// 读取陀螺仪寄存器的高8位
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);		// 读取陀螺仪寄存器的低8位
	*Gyrox = (DataH << 8) | DataL;						// 操作获得加速度计X轴的16位数据，并通过指针返回回去
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);		// 读取陀螺仪寄存器的高8位
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);		// 读取陀螺仪寄存器的低8位
	*Gyroy = (DataH << 8) | DataL;						// 操作获得加速度计Y轴的16位数据，并通过指针返回回去
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);		// 读取陀螺仪寄存器的高8位
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);		// 读取陀螺仪寄存器的低8位
	*Gyroz = (DataH << 8) | DataL;						// 操作获得加速度计Z轴的16位数据，并通过指针返回回去
}
