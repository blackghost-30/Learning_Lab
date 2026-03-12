#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * @brief  舵机初始化函数
  * @param  无
  * @retval 无
  */
void Servo_Init(void)
{
	PWM_Init();		// 初始化舵机的底层PWM
}

/*******************************************************
0          500
180        2500
*******************************************************/
/**
  * @brief  设置角度函数
  * @param  Angle 角度°
  * @retval 无
  */
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);		// 将角度线性变换，对应到舵机要求的占空比范围上
}
