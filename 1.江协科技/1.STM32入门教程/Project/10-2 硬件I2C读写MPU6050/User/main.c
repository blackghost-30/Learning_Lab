#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"

/**
  ******************************************************************************
  * @project      : STM32F103C8T6的硬件I2C读写MPU6050工程
  * @brief        : 基于硬件I2C进行MPU6050的数据读写
  * @hardware     : STM32103C8T6 + MPU6050 + OLED，采用PB10和PB11驱动，对应I2C2
  * @software     : Keil MDK + 标准外设库，工程框架为：库函数层 + 硬件驱动层 + 应用层
  * @author       : blackghost
  * @date         : 2026-03-07
  * @version      : V1
  ******************************************************************************
  */

uint8_t ID;
int16_t AX, AY, AZ, GX, GY, GZ;		// 定义变量分别用于接收XYZ轴的加速度值和陀螺仪值

int main(void)
{
	OLED_Init();
	MPU6050_Init();					// MPU6050的初始化就已经将I2C初始化了
	
	OLED_ShowString(1, 1, "ID:");
	ID = MPU6050_GetID();
	OLED_ShowHexNum(1, 4, ID, 2);
	
	while (1)
	{
		// 传入参数的地址，在子函数中直接处理参数的地址，实现指针传递
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
}
