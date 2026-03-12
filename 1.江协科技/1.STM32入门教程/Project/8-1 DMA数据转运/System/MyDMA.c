#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;

/**
  * @brief  DMA初始化
  * @param  无
  * @retval 无
  */
void MyDMA_Init(uint32_t ADDrA, uint32_t ADDrB, uint16_t Size)
{
	MyDMA_Size = Size;			// 将计数器的值存一份传给后面的函数
	
	// 第一步：开启DMA的时钟，DMA是AHB总线的设备，开启DMA1的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// 第二步：初始化DMA
	DMA_InitTypeDef DMA_InitStructure;
	
	// 下面三个函数设置外设站点的起始地址、数据宽度、是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr = ADDrA;						// 因为SRAM的地址是编译器分配的，不是固定的，所以不写绝对地址，而是写数组名来获取地址，这里传入函数的参数
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;		// 以字节大小传输
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				// 选择地址自增
	
	// 下面三个函数设置存储器站点的起始地址、数据宽度、是否自增
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADDrB;						// 这里跟上面的地址是一样的
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;		// 同上面
	DMA_InitStructure.DMA_PeripheralInc = DMA_MemoryInc_Enable;				// 同上面
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;			// 传输方向，SRC是源端的意思，就是外设站点作为源端
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;				// 是否使用自动重装，自动重装和软件触发不能同时使用，这里是存储器到存储器（也就是软件触发），选择不重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;					// 选择是否为存储器到存储器，就是选择硬件触发还是软件触发，这里是存储器到存储器也就是软件触发，选择是
	DMA_InitStructure.DMA_BufferSize = Size;					// 缓存区大小，就是传输计数器，作为参数由函数传入
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;		// 优先级，这里只有一个通道，随便选个中等
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);				// 第一个参数选择了哪个DMA和DMA的哪个通道，因为是软件触发所以选择任一个通道都可以
	
	// 第三步：开关控制，使能DMA
	DMA_Cmd(DMA1_Channel1, DISABLE);		// 不再初始化完成后就马上开始转运，而是等调用第二个函数时再开始
}

/**
  * @brief  DMA转运函数，每调用一次转运一次
  * @param  无
  * @retval 无
  */
void MyDMA_Transfer(void)
{
	// 步骤：先失能，再赋值计数器，再使能
	DMA_Cmd(DMA1_Channel1, DISABLE);						// 步骤一：失能DMA
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);		// 步骤二：赋值传输计数器
	DMA_Cmd(DMA1_Channel1, ENABLE);							// 步骤三：再次使能DMA
	
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);		// 检查转运完成的标志位，没有完成则一直循环等待
	DMA_ClearFlag(DMA1_FLAG_TC1);							// 清除标志位，需要手动清除，没有硬件自动清除
}
