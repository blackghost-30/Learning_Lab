#include "stm32f10x.h"                  // Device header
#include <time.h>                       // 导入C语言的time库

// 时间数组，存放写入寄存器的值或读出寄存器的值
uint16_t MyRTC_Time[] = {2023, 1, 1, 23, 59, 55};

void MyRTC_SetTime(void);	// 声明函数

/**
  * @brief  RTC初始化函数
  * @param  无
  * @retval 无
  */
void MyRTC_Init(void)
{
	// 第一步：开启PWR和BKP的时钟并使能对BKP和RTC的访问
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	// 借用BKP的特性判断是否需要将RTC的值复位，若都断电则复位，若只是主电源断电则不复位
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		// 第二步：开启LSE时钟，并等待LSE时钟启动完成
		RCC_LSEConfig(RCC_LSE_ON);								// 开启LSE的时钟
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);		// 获取标志位，等待时钟开启完成
		
		// 第三步：选择RTCCLK时钟源
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		// 选择LSE时钟
		RCC_RTCCLKCmd(ENABLE);						// 这里还需要使能时钟
		
		// 第四步：调用等待同步和上次写操作完成的函数
		RTC_WaitForSynchro();		// 等待同步
		RTC_WaitForLastTask();		// 等待上次操作完成
	
		// 第五步：配置预分频器，无需调用进入配置模式函数，下方函数内部包含了
		RTC_SetPrescaler(32768 - 1);	// 分频得到1Hz
		RTC_WaitForLastTask();			// 写入不是立刻完成的，需调用等待函数
	
		// 第六步：配置CNT，给一个初始时间
		MyRTC_SetTime();		// 给CNT一个初始值，不给也行，那就是默认的0
		
		// 若初始化则将DR1的位置为0xA5A5，这样就可以在初始化过后不进入这个分支复位
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else		// 即使初始化了也调用一下等待函数
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}

/**
  * @brief  RTC设置起始时间函数
  * @param  无
  * @retval 无
  */
void MyRTC_SetTime(void)
{
	// STM32中的time.h文件无法区分时区，换时区需要自己加偏移
	time_t time_cnt;		// 计数值变量
	struct tm time_data;	// 日期格式的结构体
	
	// 将数组的时间填充到time_data里面，注意偏移
	time_data.tm_year = MyRTC_Time[0] - 1900;
	time_data.tm_mon = MyRTC_Time[1] - 1;
	time_data.tm_mday = MyRTC_Time[2];	
	time_data.tm_hour = MyRTC_Time[3];
	time_data.tm_min = MyRTC_Time[4];	
	time_data.tm_sec = MyRTC_Time[5];
	
	time_cnt = mktime(&time_data) - 8 * 60 * 60;		// 日期到秒数的转换，需加上偏移
	
	RTC_SetCounter(time_cnt);		// 将秒数写入寄存器
	RTC_WaitForLastTask();			// 等待操作完成
}

/**
  * @brief  读取时间函数
  * @param  无
  * @retval 无
  */
void MyRTC_ReadTime(void)
{
	time_t time_cnt;
	struct tm time_data;
	
	time_cnt = RTC_GetCounter() + 8 * 60 * 60;		// 读取秒数，并加上偏移表示为北京时间
	
	// 这里需要先取内容再赋值，localtime默认的是伦敦时区时间，因为STM32无法识别时区
	time_data = *localtime(&time_cnt);
	
	// 将读出来的时间填充到time_data里面，注意偏移
	MyRTC_Time[0] = time_data.tm_year + 1900;
	MyRTC_Time[1] = time_data.tm_mon + 1;
	MyRTC_Time[2] = time_data.tm_mday;	
	MyRTC_Time[3] = time_data.tm_hour;
	MyRTC_Time[4] = time_data.tm_min;	
	MyRTC_Time[5] = time_data.tm_sec;
}
