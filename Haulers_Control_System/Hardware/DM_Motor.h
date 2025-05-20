#ifndef __DM_MOTOR_H__
#define __DM_MOTOR_H__

#include "can.h"

#define P_MIN -12.5f
#define P_MAX 12.5f
#define V_MIN -30.0f
#define V_MAX 30.0f
#define KP_MIN 0.0f
#define KP_MAX 500.0f
#define KD_MIN 0.0f
#define KD_MAX 5.0f
#define T_MIN -10.0f
#define T_MAX 10.0f

int float_to_uint(float x_float, float x_min, float x_max, int bits);
void DM_Motor_Enable(uint16_t Can_Id);
void DM_Motor_MIT_Ctrl(uint16_t Can_Id, float pos, float vel,float kp, float kd, float torq);
void DM_Motor_Position_Ctrl(uint16_t Can_Id, float position, float velocity);
float distanse_to_rad(float distance);
void DM_Motor_Speed_Ctrl(uint16_t Can_Id, float velocity);
float joy_to_velocity(uint8_t joy);

#endif
