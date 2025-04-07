#include "Servo.h"

void Set_Servo_Angle(int16_t angle, char servo_num)
{
	if(servo_num == 'a')
	{
		float pro1 = angle / 180.0;
		uint16_t cnt1 = (uint16_t)(500 + pro1 * 2000);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, cnt1);
	}
	if (servo_num == 'b')
	{
		float pro2 = angle / 180.0;
		uint16_t cnt2 = (uint16_t)(2500 - pro2 * 2000);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, cnt2);
	}
	if(servo_num == 'c')
	{
		float pro3 = angle / 180.0;
		uint16_t cnt3 = (uint16_t)(2500 - pro3 * 2000);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, cnt3);
	}
	if(servo_num == 'd')
	{
		float pro4 = angle / 300.0;
		uint16_t cnt4 = (uint16_t)(500 + pro4 *2000);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, cnt4);
	}
	if(servo_num == 'e')
	{
		float pro5 = angle / 180.0;
		uint16_t cnt5 = (uint16_t)(500 + pro5 * 2000);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, cnt5);
	}
}
