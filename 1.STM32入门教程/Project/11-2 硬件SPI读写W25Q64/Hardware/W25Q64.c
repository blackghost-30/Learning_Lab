#include "stm32f10x.h"                  // Device header
#include "MySPI.h"						// 引入底层
#include "W25Q64_Ins.h"					// W25Q64对应的操作集的宏定义

/**
  ******************************************************************************
  * @brief        : 这是W25Q64的硬件驱动层函数
  ******************************************************************************
  */

/**
  * @brief  硬件初始化函数
  * @param  无
  * @retval 无
  */
void W25Q64_Init(void)
{
	MySPI_Init();	// 只需要调用底层的初始化
}

/**
  * @brief  读取ID号函数
  * @param  无
  * @retval 指针实现多返回值
  */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();		// 时序开始
	MySPI_SwapByte(W25Q64_JEDEC_ID);		// 发送接收ID指令0x9F，用宏定义代替
	
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);		// 发送0xFF来读取厂商ID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);		// 发送0xFF返回设备ID的高八位
	*DID <<= 8;		// 将第一次的数据移到高八位
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);		// 发送0xFF返回设备ID的低八位，通过或操作实现
	MySPI_Stop();	// 时序结束 
}

/**
  * @brief  写使能函数，发一个指令码即可无需收数据
  * @param  无
  * @retval 无
  */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();							// 起始信号
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);	// 发送写使能指令
	MySPI_Stop();							// 不需要任何数据，直接stop
}

/**
  * @brief  读状态寄存器1，调用后跳出忙状态该函数才结束
  * @param  无
  * @retval 无
  */
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout;		// 超时变量
	MySPI_Start();			// 起始信号
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);		// 发送读寄存器1的指令
	Timeout = 10000;
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)		// 掩码取出最低位，并判断是否为1，若为1 则循环等待
	{
		Timeout --;
		if (Timeout == 0)
		{
			break;
		}
	}
	MySPI_Stop();
}

/**
  * @brief  页编程函数
  * @param  Address 写入的地址
  * @param  *DataArray 写入数组地址
  * @param  Count 写入的数量，页编程有页的限制
  * @retval 无
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	W25Q64_WriteEnable();		// 写入之前都需要先写使能
	
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);	// 发送指令码
	MySPI_SwapByte(Address >> 16);			// 发送高8位
	MySPI_SwapByte(Address >> 8);			// 发送次高位的字节
	MySPI_SwapByte(Address);				// 发送最低位的字节
	for (i = 0; i < Count; i ++)			// 循环发送所有的数据
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();		//事后等待
}

/**
  * @brief  扇区擦除函数
  * @param  Address 需要擦除的扇区的地址
  * @retval 无
  */
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();		// 写入之前都需要先写使能
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address >> 16);		// 发送高8位
	MySPI_SwapByte(Address >> 8);		// 发送次高位的字节
	MySPI_SwapByte(Address);			// 发送最低位的字节
	MySPI_Stop();
	
	W25Q64_WaitBusy();		//事后等待
}

/**
  * @brief  读取数据的函数
  * @param  Address 读取数据的地址
  * @param  *DataArray 读取数据输出数组
  * @param  Count 记录读取的数量，读取没有页的限制
  * @retval 无
  */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);	// 发送指令码
	MySPI_SwapByte(Address >> 16);		// 发送高8位
	MySPI_SwapByte(Address >> 8);		// 发送次高位的字节
	MySPI_SwapByte(Address);			// 发送最低位的字节
	for (i = 0; i < Count; i ++)		// 通过交换一个字节的程序循环读出数据
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);		//发送0xFF置换回有效的数据
	}
	MySPI_Stop();
}
