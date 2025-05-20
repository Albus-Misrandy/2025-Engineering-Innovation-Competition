#ifndef __CHASSIS_H__
#define __CHASSIS_H__

#include "DM_Motor.h"
#include "Brushed_Motor.h"
#include "Serial_Port.h"

void Go_Ahead_Position(float distance, float velocity, int16_t* encoder);
void Turning_Wheel(int16_t* encoder, float wheel_angle);
void Self_Rotation(int16_t* encoder);
void Reset_turning(int16_t* encoder);
void Go_Ahead_Velocity(uint8_t joy_v);

#endif
