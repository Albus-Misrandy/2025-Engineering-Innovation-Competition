#include "chassis.h"

void Go_Ahead(float distance, float velocity)
{
    Set_Motor_Speed(0, 'a');
    Set_Motor_Speed(0, 'b');
    Set_Motor_Speed(0, 'c');
    Set_Motor_Speed(0, 'd');
    float DM_motor_rad = distanse_to_rad(distance);
    DM_Motor_Position_Ctrl(0x101, DM_motor_rad, velocity);
    HAL_Delay(5);
    DM_Motor_Position_Ctrl(0x102, DM_motor_rad, velocity);
    HAL_Delay(5);
    DM_Motor_Position_Ctrl(0x103, DM_motor_rad, velocity);
    HAL_Delay(5);
    DM_Motor_Position_Ctrl(0x104, DM_motor_rad, velocity);
}

void Turning_Wheel(int16_t* encoder, float target_angle)
{
    Motor_Control('a', encoder[0], target_angle * 3, 0.5f, 0.0f, 0.0f);
    Motor_Control('b', encoder[1], target_angle * 3, 0.5f, 0.0f, 0.0f);
    Motor_Control('c', encoder[2], target_angle * 3, 0.5f, 0.0f, 0.0f);
    Motor_Control('d', encoder[3], target_angle * 3, 0.5f, 0.0f, 0.0f);
}

void Self_Rotation(int16_t* encoder, float velocity)
{
    Motor_Control('a', encoder[0], 45.0f, 0.5f, 0.0f, 0.0f);
    Motor_Control('b', encoder[1], -45.0f, 0.5f, 0.0f, 0.0f);
    Motor_Control('c', encoder[2], 45.0f, 0.5f, 0.0f, 0.0f);
    Motor_Control('d', encoder[3], -45.0f, 0.5f, 0.0f, 0.0f);
}
