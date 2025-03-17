#ifndef __DM_MOTOR_H__
#define __DM_MOTOR_H__

#include "can.h"
void DM_Motor_Enable(uint16_t Can_Id);
void DM_Motor_Position_Ctrl(uint16_t Can_Id, float position, float velocity);
float distanse_to_rad(float distance);

#endif
