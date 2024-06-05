/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "structures.h"
#include "cmd_JSON.h"
#include <string.h>
#include <stdlib.h>
#include "usbd_cdc_if.h"
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
char json_com [1024];
uint8_t flag_com = 0;             // флаг того, что команда пришла полностью. =1 значит можно выполнять команду
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM1_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_USB_DEVICE_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim14);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if (flag_com == 1)                                    // flag_com выставляется в usbd_cdc_if.c -> CDC_Receive_FS
	{
		JSON_INPUT(json_com);
		for (uint16_t y = 0; y < 1024; y++)               // затирание массива для новой команды
			json_com[y] = 0;
		flag_com = 0;                                     // сбрасывание флага
	}


/*----------------------------------------------------------------------------*/
	// Тест приема
//	// ф-ция ожидает получение команды с компьютера и отправляет ее обратно (flag_com выставляется в usbd_cdc_if.c -> CDC_Receive_FS)
//	if (flag_com == 1)                                    // flag_com выставляется в usbd_cdc_if.c -> CDC_Receive_FS
//	{
//		CDC_Transmit_FS(json_com, 1024);                  // отправка обратно по юсб текста команды
//		HAL_Delay(100);
//		CDC_Transmit_FS("\r\n", 2);
//		HAL_Delay(100);
//
//		for (uint16_t y = 0; y < 1024; y++)               // затирание массива для новой команды
//			json_com[y] = 0;
//		flag_com = 0;                                     // сбрасывание флага
//	}
/*----------------------------------------------------------------------------*/
//	// Тест отправки сообщения
//	HAL_Delay(1000);
//	CDC_Transmit_FS("Hello world ", 12);



//JSON_INPUT("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTC\",\"PINS\":15,\"TYPE\":\"CONTROL\"}");
//JSON_INPUT("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTF\",\"PINS\":65535,\"TYPE\":\"ADDR1\"}");
//JSON_INPUT("{\"COMMAND\":\"INFO\",\"MEMORY\":65535,\"STEP\":255}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":0}");
//JSON_INPUT("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"OUTPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}");
//
//// write
//JSON_INPUT("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":1}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":5,\"STATUS\":0,\"ACTION\":1}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":10,\"STATUS\":1,\"ACTION\":1}");
//JSON_INPUT("{\"COMMAND\":\"DELAY\",\"TIME\":\"50\",\"ACTION\":1}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":1}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":1}");
//JSON_INPUT("{\"COMMAND\":\"WRITE\"}");
//
//JSON_INPUT("{\"COMMAND\":\"INIT_GPIO\",\"MODE\":\"INPUT\",\"PORT\":\"PORTA\",\"PINS\":255,\"TYPE\":\"DATA\"}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":0}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":0}");
//
//// read
//JSON_INPUT("{\"COMMAND\":\"DATA_CHANGE\",\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":9,\"STATUS\":0,\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":6,\"STATUS\":1,\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"DELAY\",\"TIME\":\"50\",\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"READ_GPIO\",\"PORT\":\"PORTA\",\"PINS\":255,\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":2,\"STATUS\":0,\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"MODIFIC_GPIO\",\"PORT\":\"PORTC\",\"PINS\":13,\"STATUS\":1,\"ACTION\":2}");
//JSON_INPUT("{\"COMMAND\":\"READ\"}");
//
//	HAL_Delay(100000);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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
