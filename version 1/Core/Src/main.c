/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "fatfs.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay_micros.h"
#include "input_JSON.h"
#include <string.h>
#include <stdlib.h>
#include "sd.h"

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
uint8_t json_com [1024];
uint8_t flag_com = 0;             // флаг того, что команда пришла полностью. =1 значит можно выполнять команду

extern SPI_HandleTypeDef hspi2;

extern char str1[60];
uint32_t byteswritten,bytesread;
uint8_t result;
extern char USERPath[4];
FATFS SDFatFs;
FIL MyFile;
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
//  MX_I2C1_Init();
//  MX_SPI1_Init();
//  MX_TIM1_Init();
  MX_USB_DEVICE_Init();
//  MX_TIM2_Init();
//  MX_SPI2_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  DWT_Init();
  sd_init();


//  HAL_StatusTypeDef res;
//  DSTATUS status1 = 0;
//  FRESULT status2 = 0;
//  FRESULT status3 = 0;
//  FRESULT status4 = 0;
//  FRESULT status5 = 0;
//
//  uint8_t wtext[]="Hello from STM32!!!";
//  status1 = disk_initialize(SDFatFs.drv);
//  status2 = f_mount(&SDFatFs, "", 1);
//  status3 = f_open(&MyFile,"history.txt",FA_CREATE_ALWAYS|FA_WRITE);
//  status4 = f_write(&MyFile, "Hello from STM32!!!", sizeof(wtext), (void*)&byteswritten);
//  status5 = f_close(&MyFile);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//  CY62167DV30
  json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"ADDR\",\"PORT1\":\"PORTE\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\",\"PORT2\":\"PORTA\",\"PINS2\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1]\"}");
  json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"CONTROL\",\"PORT1\":\"PORTB\",\"PINS1\":\"[0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0]\"}");
  json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"DATA\",\"PORT1\":\"PORTF\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\"}");

  json_input("{\"CMD\":\"INFO\",\"MEMORY\":\"0xFFF\",\"READ\":\"3\",\"WRITE\":\"4\",\"ERASE\":\"0\",\"DELAY\":\"1\"}");
  json_input("{\"CMD\":\"WRITE_ACTION\",\"Action1\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0]\",\"STATUS\":\"High\"},\"Action2\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0]\",\"STATUS\":\"Low\"},\"Action3\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Write\"},\"Action4\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0]\",\"STATUS\":\"High\"}}");
  json_input("{\"CMD\":\"READ_ACTION\",\"Action1\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0]\",\"STATUS\":\"High\"},\"Action2\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0]\",\"STATUS\":\"Low\"},\"Action3\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Read\"}}");

  json_input("{\"CMD\":\"WRITE\"}");
  json_input("{\"CMD\":\"READ\"}");


//  24LC04B-ISN
//	json_input("{\"CMD\":\"I2C\",\"ADDR_I2C\":\"0x50\"}");
//	json_input("{\"CMD\":\"INFO\",\"MEMORY\":\"0xFFF\",\"READ\":\"1\",\"WRITE\":\"1\",\"ERASE\":\"1\"}");
//	json_input("{\"CMD\":\"WRITE_ACTION\",\"Action1\":{\"PORT\":\"I2C\",\"NUMBER\":\"0x0\",\"STATUS\":\"0xEE\"}}");
//	json_input("{\"CMD\":\"READ_ACTION\",\"Action1\":{\"PORT\":\"I2C\",\"NUMBER\":\"0x0\",\"STATUS\":\"0xFFF\"}}");
//
//	json_input("{\"CMD\":\"WRITE\"}");
//	json_input("{\"CMD\":\"READ\"}");


//  CY62128
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"ADDR\",\"PORT1\":\"PORTF\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\",\"PORT2\":\"PORTC\",\"PINS2\":\"[0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"DATA\",\"PORT1\":\"PORTA\",\"PINS1\":\"[0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"CONTROL\",\"PORT1\":\"PORTC\",\"PINS1\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1]\"}");
//
//	json_input("{\"CMD\":\"INFO\",\"MEMORY\":\"0xFFFFF\",\"READ\":\"8\",\"WRITE\":\"8\",\"ERASE\":\"1\",\"DELAY\":\"10\"}");
//	json_input("{\"CMD\":\"READ_ACTION\",\"Action1\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]\",\"STATUS\":\"High\"},\"Action2\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0]\",\"STATUS\":\"Low\"},\"Action3\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0]\",\"STATUS\":\"High\"},\"Action4\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0]\",\"STATUS\":\"Low\"},\"Action5\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Read\"},\"Action6\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0]\",\"STATUS\":\"High\"},\"Action7\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0]\",\"STATUS\":\"High\"},\"Action8\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0]\",\"STATUS\":\"Low\"}}");
//	json_input("{\"CMD\":\"WRITE_ACTION\",\"Action1\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0]\",\"STATUS\":\"High\"},\"Action2\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0]\",\"STATUS\":\"Low\"},\"Action3\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0]\",\"STATUS\":\"High\"},\"Action4\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]\",\"STATUS\":\"Low\"},\"Action5\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Write\"},\"Action6\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]\",\"STATUS\":\"High\"},\"Action7\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0]\",\"STATUS\":\"High\"},\"Action8\":{\"PORT\":\"PORTC\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0]\",\"STATUS\":\"Low\"}}");
//
//	json_input("{\"CMD\":\"WRITE\"}");
//	json_input("{\"CMD\":\"READ\"}");


//  CY62157
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"ADDR\",\"PORT1\":\"PORTE\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\",\"PORT2\":\"PORTA\",\"PINS2\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"DATA\",\"PORT1\":\"PORTF\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"CONTROL\",\"PORT1\":\"PORTB\",\"PINS1\":\"[0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0]\"}");
//
//	json_input("{\"CMD\":\"INFO\",\"MEMORY\":\"0x7FFFF\",\"READ\":\"3\",\"WRITE\":\"5\",\"ERASE\":\"0\",\"DELAY\":\"1\"}");
//	json_input("{\"CMD\":\"READ_ACTION\",\"Action1\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0]\",\"STATUS\":\"Low\"},\"Action2\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0]\",\"STATUS\":\"High\"},\"Action3\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Read\"}}");
//	json_input("{\"CMD\":\"WRITE_ACTION\",\"Action1\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0]\",\"STATUS\":\"Low\"},\"Action2\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0]\",\"STATUS\":\"High\"},\"Action3\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0]\",\"STATUS\":\"Low\"},\"Action4\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Write\"},\"Action5\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0]\",\"STATUS\":\"High\"}}");
//
//	json_input("{\"CMD\":\"WRITE\"}");
//	json_input("{\"CMD\":\"READ\"}");


//  FM28V020-SGx
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"ADDR\",\"PORT1\":\"PORTE\",\"PINS1\":\"[0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"DATA\",\"PORT1\":\"PORTF\",\"PINS1\":\"[0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"CONTROL\",\"PORT1\":\"PORTB\",\"PINS1\":\"[0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0]\"}");
//
//	json_input("{\"CMD\":\"INFO\",\"MEMORY\":\"0x3FFFF\",\"READ\":\"3\",\"WRITE\":\"5\",\"ERASE\":\"8\",\"DELAY\":\"5\"}");
//	json_input("{\"CMD\":\"READ_ACTION\",\"Action1\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0]\",\"STATUS\":\"High\"},\"Action2\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0]\",\"STATUS\":\"Low\"},\"Action3\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Read\"}}");
//	json_input("{\"CMD\":\"WRITE_ACTION\",\"Action1\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0]\",\"STATUS\":\"Low\"},\"Action2\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0]\",\"STATUS\":\"High\"},\"Action3\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0]\",\"STATUS\":\"Low\"},\"Action4\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Write\"},\"Action5\":{\"PORT\":\"PORTB\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0]\",\"STATUS\":\"High\"}}");
//
//	json_input("{\"CMD\":\"WRITE\"}");
//	json_input("{\"CMD\":\"READ\"}");


//  IS61LV25616AL
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"ADDR\",\"PORT1\":\"PORTE\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\",\"PORT2\":\"PORTD\",\"PINS2\":\"[0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"DATA\",\"PORT1\":\"PORTF\",\"PINS1\":\"[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]\"}");
//	json_input("{\"CMD\":\"GPIO\",\"FUNC\":\"CONTROL\",\"PORT1\":\"PORTD\",\"PINS1\":\"[0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1]\"}");
//
//	json_input("{\"CMD\":\"INFO\",\"MEMORY\":\"0x7FFFF\",\"READ\":\"3\",\"WRITE\":\"5\",\"ERASE\":\"0\",\"DELAY\":\"1\"}");
//	json_input("{\"CMD\":\"READ_ACTION\",\"Action1\":{\"PORT\":\"PORTD\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1]\",\"STATUS\":\"Low\"},\"Action2\":{\"PORT\":\"PORTD\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0]\",\"STATUS\":\"High\"},\"Action3\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Read\"}}");
//	json_input("{\"CMD\":\"WRITE_ACTION\",\"Action1\":{\"PORT\":\"PORTD\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1]\",\"STATUS\":\"Low\"},\"Action2\":{\"PORT\":\"PORTD\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0]\",\"STATUS\":\"High\"},\"Action3\":{\"PORT\":\"PORTD\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0]\",\"STATUS\":\"Low\"},\"Action4\":{\"PORT\":\"0\",\"NUMBER\":\"0\",\"STATUS\":\"Write\"},\"Action5\":{\"PORT\":\"PORTD\",\"NUMBER\":\"[0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0]\",\"STATUS\":\"High\"}}");
//
//	json_input("{\"CMD\":\"WRITE\"}");
//	json_input("{\"CMD\":\"READ\"}");



	HAL_Delay(10000);
//	json_input("");


	// ф-ция ожидает получение команды с компьютера и отправляет ее обратно (flag_com выставляется в usbd_cdc_if.c -> CDC_Receive_FS)
/*	if (flag_com == 1)                                    // flag_com выставляется в usbd_cdc_if.c -> CDC_Receive_FS
	{
		CDC_Transmit_FS(json_com, 1024);                  // отправка обратно по юсб текста команды
		HAL_Delay(100);
		CDC_Transmit_FS("\r\n", 2);
		HAL_Delay(100);

		for (uint16_t y = 0; y < 1024; y++)               // затирание массива для новой команды
			json_com[y] = 0;
		flag_com = 0;                                     // сбрасывание флага
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