#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	// 第一步：开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		// 开启ADC1的时钟，且ADC都是APB2上的设备
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);		// 为ADC的CLK时钟进行配置，选择6分频，12MHz
	
	// 第二步：配置GPIO，将其配置为模拟输入的引脚
	GPIO_InitTypeDef GPIO_InitStructure;				// 定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		// 模拟输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;	// 四路输入，需要将所有的四个GPIO口初始化
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 第三步：配置规则组的输入通道
	
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	// 这里不需要再配置输入通道了，直接在后面的GetValue函数中作为参数传入
	
	// 第四步：配置ADC转换器，选择单次非扫描模式
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;						// 选择是否为连续转换模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					// 数据对齐，选择右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		// 选择外部触发模式，就是START信号，用软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						// 选择为独立模式而非双ADC模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;									// 通道的数目
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;							// 选择扫描模式还是非扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 第五步：若要用中断和看门狗可在这部分配置，这节代码不用
	
	// 第六步：开启ADC的电源
	ADC_Cmd(ADC1, ENABLE);
	
	// 第七步：对ADC进行校准
	ADC_ResetCalibration(ADC1);								// 第一步：复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);		// 第二步：等待标志位
	ADC_StartCalibration(ADC1);								// 第三步：开始校准，内部电路自行进行校准，不需要理会
	while (ADC_GetCalibrationStatus(ADC1) == SET);			// 第四步：等待校准完成，该函数用于获取校准状态;
}

/**
  * @brief  获取转换结果函数
  * @param  ADC_Channel 传入的通道
  * @retval 获取的数值
  */
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);		// 配置通道，通过函数调用不断更改通道实现“扫描”功能
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			// 软件触发
	
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);			// 取结果，读取寄存器后自动清除标志位，不需要手动清除
}

