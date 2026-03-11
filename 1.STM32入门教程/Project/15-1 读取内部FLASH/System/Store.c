#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"

#define STROE_START_ADDRESS		0x0800FC00	// 定义最后一页的起始地址
#define STROE_COUNT				512			// 定义SRAM数组的大小

// 用SRAM缓存数组管理FLASH的最后一页
uint16_t Store_Data[STROE_COUNT];

/**
  * @brief  闪存初始化函数
  * @param  无
  * @retval 无
  */
void Store_Init(void)
{
	// 读取最后一页的第一个半字当标志位，0xA5A5是自己定义的标志位，若不是该值证明是第一次使用
	if (MyFLASH_ReadHalfWord(STROE_START_ADDRESS) != 0xA5A5)
	{
		MyFLASH_ErasePage(STROE_START_ADDRESS);					// 若是第一次使用则将最后一页给擦除
		MyFLASH_ProgramHalfWord(STROE_START_ADDRESS, 0xA5A5);	// 手动写入标志位
		for (uint16_t i = 1; i < STROE_COUNT; i ++)				// 注意这里的i从1开始，因为第一个位是标志位
		{
			MyFLASH_ProgramHalfWord(STROE_START_ADDRESS + i * 2, 0x0000);	// 将最后一页剩下的全部数据写为0
		}
	}
	
	// 上电时将闪存备份数据恢复到SRAM数组，标志位也一块传过去
	for (uint16_t i = 0; i < STROE_COUNT; i ++)
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(STROE_START_ADDRESS + i * 2);	// 这里乘2是因为半字对应两个字节
	}
}

/**
  * @brief  SRAM数组备份函数
  * @param  无
  * @retval 无
  */
void Store_Save(void)
{
	MyFLASH_ErasePage(STROE_START_ADDRESS);
	for (uint16_t i = 0; i < STROE_COUNT; i ++)
	{
		MyFLASH_ProgramHalfWord(STROE_START_ADDRESS + i * 2, Store_Data[i]);
	}
}

/**
  * @brief  闪存清零函数
  * @param  无
  * @retval 无
  */
void Store_Clear(void)
{
	for (uint16_t i = 1; i < STROE_COUNT; i ++)    // 注意别把标志位给清零了
	{
		Store_Data[i] = 0x0000;
	}
	Store_Save();		// 把SRAM数组数据更新到闪存
}
