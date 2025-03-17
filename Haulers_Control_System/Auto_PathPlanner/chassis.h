#ifndef __CHASSIS_H__
#define __CHASSIS_H__

#include "DM_Motor.h"
#include "Brushed_Motor.h"

void Go_Ahead(float distance, float velocity);
void Turning_Wheel(int16_t* encoder, float wheel_angle);
void Self_Rotation(int16_t* encoder, float velocity);

#endif
