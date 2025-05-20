/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Key.h"
#include "PS2_JoyStick.h"
#include "Brushed_Motor.h"
#include "Serial_Port.h"
#include "DM_Motor.h"
#include "Servo.h"
#include "OledScreen.h"
#include "chassis.h"
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int16_t encoder_count[4] = {0, 0, 0, 0};

int32_t time_ms = 0;
float DM_motor_rad = 0;
bool key_num = false;
bool motion_num = false;
JOYSTICK_TypeDef main_joy;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim==&htim4)
  {
    time_ms++;
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0)
	{
		uint8_t f0_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0);
		uint8_t f5_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_5);
		if(f0_state == GPIO_PIN_SET)
    {
		  if(f5_state == GPIO_PIN_RESET)
      {
        encoder_count[0]++;
      }
      else
      {
        encoder_count[0]--;
      }
    }
    if (f0_state == GPIO_PIN_RESET)
    {
      if (f5_state == GPIO_PIN_RESET)
      {
        encoder_count[0]--;
      }
      else
      {
        encoder_count[0]++;
      }
    }
	}
  if (GPIO_Pin == GPIO_PIN_1)
  {
    uint8_t f1_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_1);
		uint8_t f6_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6);
    if (f1_state == GPIO_PIN_SET)
    {
      if (f6_state == GPIO_PIN_RESET)
      {
        encoder_count[1]++;
      }
      else
      {
        encoder_count[1]--;
      }
    }
    if (f1_state == GPIO_PIN_RESET)
    {
      if (f6_state == GPIO_PIN_RESET)
      {
        encoder_count[1]--;
      }
      else
      {
        encoder_count[1]++;
      }
    } 
  }
  if (GPIO_Pin == GPIO_PIN_2)
  {
    uint8_t f2_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_2);
		uint8_t f7_state = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7);
    if (f2_state == GPIO_PIN_SET)
    {
      if (f7_state == GPIO_PIN_RESET)
      {
        encoder_count[2]++;
      }
      else
      {
        encoder_count[2]--;
      }
    }
    if (f2_state == GPIO_PIN_RESET)
    {
      if (f7_state == GPIO_PIN_RESET)
      {
        encoder_count[2]--;
      }
      else
      {
        encoder_count[2]++;
      }
    }
  }
  if (GPIO_Pin == GPIO_PIN_8)
  {
    uint8_t f3_state = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
		uint8_t f4_state = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
    if (f3_state == GPIO_PIN_SET)
    {
      if (f4_state == GPIO_PIN_RESET)
      {
        encoder_count[3]++;
      }
      else
      {
        encoder_count[3]--;
      }
    }
    if (f3_state == GPIO_PIN_RESET)
    {
      if (f4_state == GPIO_PIN_RESET)
      {
        encoder_count[3]--;
      }
      else
      {
        encoder_count[3]++;
      }
    }
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart1)
  {
    
  }
  
}

// void get_d_encoder(void)
// {
//   encoder_count[3] = __HAL_TIM_GET_COUNTER(&htim2);
// }

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_CAN_Init();
  MX_TIM8_Init();
  MX_I2C1_Init();
  MX_TIM6_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_2);
  
  HAL_TIM_Base_Start_IT(&htim4);
  // OLED_Init();
  Can_Init();
  DM_Motor_Enable(0x001);
  HAL_Delay(5);
  DM_Motor_Enable(0x002);
  HAL_Delay(5);
  DM_Motor_Enable(0x003);
  HAL_Delay(5);
  DM_Motor_Enable(0x004);
  HAL_Delay(5);
  DM_Motor_Enable(0x105);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  { 
    PS2_Scanning(&main_joy);
    HAL_Delay(30);
    // send_16bitsfloat_data(encoder_count[3]);
    uint8_t LU = main_joy.LJoy_UD;
    uint8_t m = main_joy.mode;
    if (m == 0x73)
    {
      Go_Ahead_Velocity(LU);
      if (main_joy.btn2 & (1 << 0))
      {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        uint64_t start1 = time_ms;
        while ((time_ms - start1) < 1200)
        {
          Reset_turning(encoder_count);
        }
      }
      if (main_joy.btn2 & (1 << 1))
      {
        // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        Set_Servo_Angle(40, 'b');
        Set_Servo_Angle(60, 'a');
        Set_Servo_Angle(75, 'c');
        // Set_Servo_Angle(150, 'd');
      }
      if (main_joy.btn2 & (1 << 2))
      {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        uint64_t start0 = time_ms;
        while ((time_ms - start0) < 1200)
        {
          Self_Rotation(encoder_count);
        }
      }
      if (main_joy.btn2 & (1 << 3))
      {
        // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        Set_Servo_Angle(0, 'a');
        Set_Servo_Angle(0, 'b');
        Set_Servo_Angle(0, 'c');
        // Set_Servo_Angle(150, 'd');
      }
      if (main_joy.btn2 & (1 << 6))
      {
        key_num = !key_num;
      }
      if (key_num == false)
      {
        Set_Servo_Angle(130, 'e');
      }
      if (key_num == true)
      {
        Set_Servo_Angle(50, 'e');
      }
    }
    
    
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
