#include "PS2_JoyStick.h"

const uint8_t PS2_command[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t PS2_data[9] = {0};

void Delay_us(uint32_t us)
{
    __HAL_TIM_SET_COUNTER(&htim6, 0);
    HAL_TIM_Base_Start(&htim6);
    while (__HAL_TIM_GET_COUNTER(&htim6) < us);
    HAL_TIM_Base_Stop(&htim6);
}

void CMD_H(void)
{
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_SET);
}

void CMD_L(void)
{
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_12, GPIO_PIN_RESET);
}

void CS_H(void)
{
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
}

void CS_L(void)
{
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
}

void CLK_H(void)
{
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
}

void CLK_L(void)
{
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
}

void PS2_JoyStick_Init(void)
{
    CS_H();
}


static uint8_t PS2_ReadAndWrite(uint8_t command)
{
    volatile uint8_t res = 0;
	volatile uint8_t ref;
    for (uint8_t ref = 0x01; ref > 0x00; ref <<= 1)
    {
        if (ref&command)
        {
            CMD_H();
        }
        else
        {
            CMD_L();
        }
        
        CLK_L();
        Delay_us(16);

        if (HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_11))
        {
            res |= ref;
        }
        CLK_H();
        Delay_us(16);
    }
    return res;
}

void PS2_Scanning(JOYSTICK_TypeDef * ps2)
{
    CS_L();
    for (uint8_t i = 0; i < 9; i++)
    {
        PS2_data[i] = PS2_ReadAndWrite(PS2_command[i]);
    }
    CS_H();

    ps2->mode = PS2_data[1];
    ps2->btn1 = ~PS2_data[3];
    ps2->btn2 = ~PS2_data[4];
    ps2->RJoy_LR = PS2_data[5];
    ps2->RJoy_UD = PS2_data[6];
    ps2->LJoy_LR = PS2_data[7];
    ps2->LJoy_UD = PS2_data[8];
}
