#include "Key.h"

uint8_t KeyPush(uint8_t KeyNum)
{
	HAL_Init();

	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET);
		HAL_Delay(20);
		if (KeyNum == 0)
		{
			KeyNum = 1;
		}
		else
		{
			KeyNum = 0;
		}
		
	}
	return KeyNum;
}
