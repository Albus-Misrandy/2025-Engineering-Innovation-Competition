#include "DM_Motor.h"

uint8_t Standard_Type = 0;
uint8_t data_len = 8;
uint8_t data_v_len = 4;

/**
************************************************************************
* @brief:      	float_to_uint: 浮点数转换为无符号整数函数
* @param[in]:   x_float:	待转换的浮点数
* @param[in]:   x_min:		范围最小值
* @param[in]:   x_max:		范围最大值
* @param[in]:   bits: 		目标无符号整数的位数
* @retval:     	无符号整数结果
* @details:    	将给定的浮点数 x 在指定范围 [x_min, x_max] 内进行线性映射，映射结果为一个指定位数的无符号整数
************************************************************************
**/
int float_to_uint(float x_float, float x_min, float x_max, int bits)
{
	/* Converts a float to an unsigned int, given range and number of bits */
	float span = x_max - x_min;
	float offset = x_min;
	return (int) ((x_float-offset)*((float)((1<<bits)-1))/span);
}


void DM_Motor_Enable(uint16_t Can_Id)
{
    uint8_t enable_data[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC};
    Can_send_data(Standard_Type, Can_Id, data_len, enable_data);
}

void DM_Motor_MIT_Ctrl(uint16_t Can_Id, float pos, float vel,float kp, float kd, float torq)
{
    uint16_t pos_tmp,vel_tmp,kp_tmp,kd_tmp,tor_tmp;
    uint8_t data[8];

    pos_tmp = float_to_uint(pos, P_MIN, P_MAX, 16);
	vel_tmp = float_to_uint(vel, V_MIN, V_MAX, 12);
	kp_tmp  = float_to_uint(kp, KP_MIN, KP_MAX, 12);
	kd_tmp  = float_to_uint(kd, KD_MIN, KD_MAX,12);
	tor_tmp = float_to_uint(torq, T_MIN, T_MAX, 12);

	data[0] = (pos_tmp >> 8);
	data[1] = pos_tmp;
	data[2] = (vel_tmp >> 4);
	data[3] = ((vel_tmp&0xF)<<4)|(kp_tmp>>8);
	data[4] = kp_tmp;
	data[5] = (kd_tmp >> 4);
	data[6] = ((kd_tmp&0xF)<<4)|(tor_tmp>>8);
	data[7] = tor_tmp;

    Can_send_data(Standard_Type, Can_Id, data_len, data);
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

void DM_Motor_Speed_Ctrl(uint16_t Can_Id, float velocity)
{
    uint8_t *vbuf;
	uint8_t data[4];
	
	vbuf=(uint8_t*)&velocity;
	
	data[0] = *vbuf;
	data[1] = *(vbuf+1);
	data[2] = *(vbuf+2);
	data[3] = *(vbuf+3);

    Can_send_data(Standard_Type, Can_Id, data_v_len, data);
}

float distanse_to_rad(float distance)
{
    float circle = 3.1416 * 64.0f;
    float wheel_rotations = distance / circle;
    float motor_rotations = wheel_rotations * 1.42;
    float motor_rad = motor_rotations * 120.637;
    return motor_rad;
}

float joy_to_velocity(uint8_t joy)
{
    float err = joy - 127;
    float pr;
    if (err >= 0)
    {
        pr = err / 127;
        float v = pr * 2;
        return -v;
    }
    if (err < 0)
    {
        pr = -err / 127;
        float v = pr * 2;
        return v;
    }
    else
    {
        return 0.0f;
    }
}
