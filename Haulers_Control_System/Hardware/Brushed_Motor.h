#ifndef __BRUSHED_MOTOR_H__
#define __BRUSHED_MOTOR_H__

#include "gpio.h"
#include "tim.h"

typedef struct {
    float Kp;
    float Ki;
    float Kd;    // PID参数
    float target;         // 目标位置（编码器计数值）
    float integral;       // 积分项
    float prev_error;     // 上一次误差
  } PID_Controller;

void Set_Motor_Speed(int16_t speed, char motorNum);
int16_t Counting_Encoder(uint8_t a_state, uint8_t b_state, int16_t encoder_count);
int8_t Get_Direction(uint8_t a_state, uint8_t b_state, int8_t direction);
float Get_Angle(int16_t encoder_count);
void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd);
float PID_Update(PID_Controller *pid, float current_pos, float target_pos, float Kp, float Ki, float Kd);
void Motor_Control(char Motor_num, float current_pos, float target_pos, float Kp, float Ki, float Kd);

#endif
