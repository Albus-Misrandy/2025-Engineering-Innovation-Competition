#ifndef __PS2_JOYSTICK_H__
#define __PS2_JOYSTICK_H__

#include "gpio.h"
#include "tim.h"

/* 手柄数据结构体 */
typedef struct {
    uint8_t mode;       // 工作模式
    uint8_t btn1;       // 按钮组1
    uint8_t btn2;       // 按钮组2
    uint8_t RJoy_LR;    // 右摇杆左右
    uint8_t RJoy_UD;    // 右摇杆上下
    uint8_t LJoy_LR;    // 左摇杆左右
    uint8_t LJoy_UD;    // 左摇杆上下
} JOYSTICK_TypeDef;

void CMD_H(void);
void CMD_L(void);
void CS_H(void);
void CS_L(void);
void CLK_H(void);
void CLK_L(void);
void PS2_JoyStick_Init(void);
void PS2_Scanning(JOYSTICK_TypeDef * ps2);
void Delay_us(uint32_t us);

#endif
