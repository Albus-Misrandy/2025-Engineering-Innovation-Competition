#include "DM_Motor.h"

uint8_t Standard_Type = 0;
uint8_t data_len = 8;

void DM_Motor_Enable(uint16_t Can_Id)
{
    uint8_t enable_data[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC};
    Can_send_data(Standard_Type, Can_Id, data_len, enable_data);
}

void DM_Motor_Position_Ctrl(uint16_t Can_Id, float position, float velocity)
{
    uint8_t *pos_buf, *vel_buf;
    uint8_t data[8];
    pos_buf = (uint8_t*)&position;
    vel_buf = (uint8_t*)&velocity;
    data[0] = *pos_buf;
    data[1] = *(pos_buf + 1);
    data[2] = *(pos_buf + 2);
    data[3] = *(pos_buf + 3);
    data[4] = *vel_buf;
    data[5] = *(vel_buf + 1);
    data[6] = *(vel_buf + 2);
    data[7] = *(vel_buf + 3);

    Can_send_data(Standard_Type, Can_Id, data_len, data);
}

float distanse_to_rad(float distance)
{
    float circle = 3.1416 * 64.0f;
    float wheel_rotations = distance / circle;
    float motor_rotations = wheel_rotations * 1.42;
    float motor_rad = motor_rotations * 120.637;
    return motor_rad;
}
