#include "Servo.h"

void Set_Servo_Angle(int16_t angle, char servo_num)
{
	if (servo_num == 'a')
	{
		uint16_t cnt1 = 500 + (angle / 300) * 2000;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, cnt1);
	}
	if (servo_num == 'b')
	{
		uint16_t cnt2 = 500 + (angle / 180) * 2000;  // 不确定是否是180度舵机
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, cnt2);
	}
	if (servo_num == 'c')
	{
		uint16_t cnt3 = 500 + (angle / 180) * 2000;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, cnt3);
	}		
}
