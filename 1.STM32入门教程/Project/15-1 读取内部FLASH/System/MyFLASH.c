#include "stm32f10x.h"                  // Device header


/*******************************************************************************
	FLASH不需要初始化，所以直接开始写操作函数
*******************************************************************************/

/**
  * @brief  以32位的形式读取某个地址下的值
  * @param  Address 指定的地址
  * @retval 地址下的数据
  */
uint32_t MyFLASH_ReadWord(uint32_t Address) 
{
	return *((__IO uint32_t *)(Address));	// 以32位直接访问特定地址的内容 
}

/**
  * @brief  以半字的形式读取某个地址的值
  * @param  Address 指定的地址
  * @retval 地址下的数据
  */
uint16_t MyFLASH_ReadHalfWord(uint32_t Address) 
{
	return *((__IO uint16_t *)(Address));	// 以16位直接访问特定地址的内容 
}

/**
  * @brief  以字节的形式读取某个地址的值
  * @param  Address 指定的地址
  * @retval 地址下的数据
  */
uint8_t MyFLASH_ReadByte(uint32_t Address) 
{
	return *((__IO uint8_t *)(Address));	// 以8位直接访问特定地址的内容 
}

/**
  * @brief  全擦除函数
  * @param  无
  * @retval 无
  */
void MyFLASH_EraseAllPages(void)
{
	FLASH_Unlock();				// 先进行解锁
	FLASH_EraseAllPages();		// 擦除所有的页
	FLASH_Lock();				// 重新再锁上
}

/**
  * @brief  页擦除函数
  * @param  无
  * @retval 无
  */
void MyFLASH_ErasePage(uint32_t PageAddress)
{
	FLASH_Unlock();					// 先进行解锁
	FLASH_ErasePage(PageAddress);	// 传入地址进行页擦除
	FLASH_Lock();					// 重新再锁上
}

/**
  * @brief  编程一个字的函数
  * @param  Address 要写入的地址
  * @param  Data 要写入的全字
  * @retval 无
  */
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
	FLASH_Unlock();						// 先进行解锁
	FLASH_ProgramWord(Address, Data);	// 传入地址进行页擦除
	FLASH_Lock();						// 重新再锁上
}

/**
  * @brief  编程半字的函数
  * @param  Address 要写入的地址
  * @param  Data 要写入的半字
  * @retval 无
  */
void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
	FLASH_Unlock();							// 先进行解锁
	FLASH_ProgramHalfWord(Address, Data);	// 传入地址进行页擦除
	FLASH_Lock();							// 重新再锁上
}
