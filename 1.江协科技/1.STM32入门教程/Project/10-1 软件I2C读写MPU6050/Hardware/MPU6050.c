#include "stm32f10x.h"            // Device header
#include "MyI2C.h"                //此模块要建立在MyI2C的基础上
#include "MPU6050_Reg.h"          //将宏定义6050寄存器的头文件加上

#define MPU6050_ADDRESS			0xD0			//宏定义MPU6050的地址

/**
  * @brief  指定地址写的函数封装
  * @param  RegAddress 地址
  * @param  Data 要写入的数据
  * @retval 无
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	MyI2C_Start();						// 产生起始条件
	MyI2c_SendByte(MPU6050_ADDRESS);	// 第一个字节：发送地址＋读写位
	MyI2C_ReceiveAck();					// 接收应答位
	MyI2c_SendByte(RegAddress);			// 第二个字节：发送指定的寄存器地址
	MyI2C_ReceiveAck();					// 接收应答位
	// 若要发送多个字节，就可在后面两句套一个for循环
	MyI2c_SendByte(Data);				// 第三个字节：发送要写入寄存器的数据
	MyI2C_ReceiveAck();					// 接收应答位
	MyI2C_Stop();						// 产生终止条件
}

/**
  * @brief  指定地址读的函数封装
  * @param  RegAddress 地址
  * @retval 读取到的数据
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	// 下面的这部分代码与指定地址写是一样的，指定了地址但是还没来得及写
	MyI2C_Start();						// 产生起始条件
	MyI2c_SendByte(MPU6050_ADDRESS);	// 第一个字节：发送地址＋读写位
	MyI2C_ReceiveAck();					// 接收应答位
	MyI2c_SendByte(RegAddress);			// 第二个字节：发送指定的寄存器地址
	MyI2C_ReceiveAck();					// 接收应答位
	
	// 上面是写的程序，将当前寄存器的地址指定到了想要的位置；下面是读的时序，需要产生重复起始位Sr
	MyI2C_Start();								// 产生起始位
	MyI2c_SendByte(MPU6050_ADDRESS | 0x01);		// 将读写位置位1，即读
	MyI2C_ReceiveAck();							// 接收应答位
	
	// 这里要读多个字节的话将下面两句套for循环，同时要加上给应答的语句
	Data = MyI2C_ReceiveByte();					// 接收数据
	MyI2c_SendAck(1);							// 给1表示没有应答，主机不想再要了
	MyI2C_Stop();
	
	return Data;
}

/**
  * @brief  初始化函数
  * @param  无
  * @retval 无
  */
void MPU6050_Init(void)
{
	// 先把底层初始化
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);			// 配置电源管理寄存器1，这里解除其睡眠状态，并选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);			// 配置电源管理寄存器2，将所有位设置为不待机，即6个轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);			// 配置采样率分频，这里给10分频
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);				// MPU6050的配置寄存器，滤波参数给最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);		// 陀螺仪配置寄存器，选择最大量程，16g，最大参数为32768，通过数据除以32768再乘以量程即为真是的加速度值
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);		// 加速度计配置寄存器，选择最大量程，同理上面
}

/**
  * @brief  获取芯片ID的函数
  * @param  无
  * @retval 无
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
