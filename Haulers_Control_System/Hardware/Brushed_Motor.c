#include "Brushed_Motor.h"
#include "Serial_Port.h"

PID_Controller pid;

void Set_Motor_Speed(int16_t speed, char motorNum)
{
	if(motorNum == 'a')
	{
		if(speed > 0)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, speed);
		}
		if(speed < 0)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -speed);
		}
		if(speed == 0)
		{
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2);
		}
	}
	if(motorNum == 'b')
	{
		if(speed > 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_SET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, speed);
		}
		if(speed < 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, -speed);
		}
		if(speed == 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 2);
		}
	}
	if(motorNum == 'c')
	{
		if(speed > 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, speed);
		}
		if(speed < 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, -speed);
		}
		if(speed == 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 2);
		}
	}
	if(motorNum == 'd')
	{
		if(speed > 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_SET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, speed);
		}
		if(speed < 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, -speed);
		}
		if(speed == 0)
		{
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 2);
		}
	}
}

float Get_Angle(int16_t encoder_count)
{
    float PPR = 960.0f;
    float deg = (encoder_count / PPR) * 360;
	return deg;
}

float PID_Update(PID_Controller *pid, float current_pos, float target_pos, float Kp, float Ki, float Kd) 
{
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->target = (target_pos / 360) * 960;
	float error = pid->target - current_pos;
    pid->integral += error; // 积分项
    float derivative = (error - pid->prev_error); // 微分项
    float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
    pid->prev_error = error;
	if (error < 50 && error > -50)
	{
		output = 0;
	}
	// send_16bitsfloat_data(error);
	return output;
  }

void Motor_Control(char Motor_num, float current_pos, float target_pos, float Kp, float Ki, float Kd) 
{
	// PID计算
	float output = PID_Update(&pid, current_pos, target_pos, Kp, Ki, Kd);
  
	// 输出限幅（例如±100%占空比）
	output = (output > 60) ? 60 : (output < -60) ? -60 : output;
	//send_16bitsfloat_data(output);
	int16_t pwm_output = (int16_t)output;
	
	Set_Motor_Speed(pwm_output, Motor_num);
}
