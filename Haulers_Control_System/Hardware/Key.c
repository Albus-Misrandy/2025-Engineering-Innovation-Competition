#include "Key.h"

uint8_t Get_KeyNumber(void)
{
    uint8_t KeyNum = 2;
    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET)
    {
        HAL_Delay(15);
        while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET);
        HAL_Delay(15);
        KeyNum = 0;
    }
    return KeyNum;
}
