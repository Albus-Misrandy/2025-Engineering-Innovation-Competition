#include "chassis.h"

void Go_Ahead_Position(float distance, float velocity, int16_t* encoder)
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

void Self_Rotation(int16_t* encoder)
{
    Motor_Control('a', encoder[0], -405.0f, 0.5f, 0.001f, 2.0f);
    Motor_Control('b', encoder[1], 405.0f, 0.5f, 0.001f, 2.0f);
    Motor_Control('c', encoder[2], 155.0f, 0.5f, 0.001f, 2.0f);
    Motor_Control('d', encoder[3], -125.0f, 0.5f, 0.001f, 2.0f);
}

void Reset_turning(int16_t* encoder)
{
    Motor_Control('a', encoder[0], 0.0f, 0.5f, 0.001f, 3.0f);
    Motor_Control('b', encoder[1], 0.0f, 0.5f, 0.001f, 3.0f);
    Motor_Control('c', encoder[2], 10.0f, 0.5f, 0.001f, 3.0f);
    Motor_Control('d', encoder[3], 0.0f, 0.5f, 0.001f, 3.0f);
}

void Go_Ahead_Velocity(uint8_t joy_v)
{
    Set_Motor_Speed(0, 'a');
    Set_Motor_Speed(0, 'b');
    Set_Motor_Speed(0, 'c');
    Set_Motor_Speed(0, 'd');
    float v = joy_to_velocity(joy_v);
    send_16bitsfloat_data(v);
    DM_Motor_MIT_Ctrl(0x001, 0.0f, v, 0.0f, 0.54f, 0.0f);
    HAL_Delay(5);
    DM_Motor_MIT_Ctrl(0x002, 0.0f, v, 0.0f, 0.54f, 0.0f);
    HAL_Delay(5);
    DM_Motor_MIT_Ctrl(0x003, 0.0f, v, 0.0f, 0.54f, 0.0f);
    HAL_Delay(5);
    DM_Motor_MIT_Ctrl(0x004, 0.0f, v, 0.0f, 0.54f, 0.0f);
}
