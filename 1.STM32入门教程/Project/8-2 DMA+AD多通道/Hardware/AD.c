#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];
void AD_Init(void)
{
	// 第一步：开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		// 开启ADC1的时钟，且ADC都是APB2上的设备
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		// 开启GPIOA的时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);			// 为ADC的CLK时钟进行配置，选择6分频，12MHz
	
	// 第二步：配置GPIO，将其配置为模拟输入的引脚
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;										// 定义结构体的模式为模拟输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	// 四路输入，需要将所有的四个GPIO口初始化
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第三步：配置规则组的输入通道，即是“点菜过程”，配置ADC的四个通道，实现扫描模式
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	// 第四步：配置ADC转换器，选择连续扫描模式
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						// 选择为连续转换模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					// 数据对齐，选择右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		// 这里选择外部触发模式，就是START信号
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						// 选择为独立模式而非双ADC模式
	ADC_InitStructure.ADC_NbrOfChannel = 4;									// 通道的数目为4
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;							// 选择扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 第五步：下面是配置DMA的函数
	// 第一步：开启DMA的时钟，注意DMA是AHB总线的设备，开启DMA1的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// 第二步：初始化DMA
	DMA_InitTypeDef DMA_InitStructure;
	// 下面三个函数设置外设站点的起始地址、数据宽度、是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC1->DR;				// 源头，ADC转换完成后数据存在ADC_DR寄存器里，所以这里选择为ADC_DR寄存器
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;		// 这里要DR寄存器低16位数据
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;				// 选择地址不自增，始终转运同一个位置的值
	// 下面三个函数设置存储器站点的起始地址、数据宽度、是否自增
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)AD_Value;				// 将目的地的基地址传入
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_HalfWord;		// 同上面
	DMA_InitStructure.DMA_PeripheralInc = DMA_MemoryInc_Enable;					// 存储器的地址是自增的，需要区分这里和上面
	// 配置DMA的参数
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;		// 传输方向，外设站点作为源端
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;			// 这里选择循环模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;			// 选择是否为存储器到存储器，选择硬件触发还是软件触发，选择硬件触发，触发源是ADC1
	DMA_InitStructure.DMA_BufferSize = 4;					// 缓存区大小，就是传输计数器，作为参数由函数传入
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;	// 优先级，这里只有一个通道，随便选个中等
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);			// 第一个参数选择了哪个DMA和DMA的哪个通道，ADC1只接在了DMA1的通道1上，所以需要选择DMA1_Channel1
	// 第三步：开关控制，使能DMA
	DMA_Cmd(DMA1_Channel1, ENABLE);							// 直接使能，因为是硬件触发，需要等有DMA请求时才转运
	
	// 第六步：开启DMA的触发信号（重点，别忘）
	ADC_DMACmd(ADC1, ENABLE);
	
	// 第七步：开启ADC的电源
	ADC_Cmd(ADC1, ENABLE);
	
	// 第八步：对ADC进行校准
	ADC_ResetCalibration(ADC1);								// 第一步：复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);		// 第二步：等待标志位
	ADC_StartCalibration(ADC1);								// 第三步：开始校准，内部电路自行进行校准，不需要理会
	while (ADC_GetCalibrationStatus(ADC1) == SET);			// 第四步：等待校准完成，该函数用于获取校准状态;
	
	// 第九步：初始化时先将ADC进行软件触发，注意ADC的软件触发和DMA的软件触发的区别
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					// 软件触发
}
