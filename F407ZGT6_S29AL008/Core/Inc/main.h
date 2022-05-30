/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void DATA_OUT(void);
void DATA_IN(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OE_Pin GPIO_PIN_3
#define OE_GPIO_Port GPIOB
#define CE_Pin GPIO_PIN_4
#define CE_GPIO_Port GPIOB
#define WE_Pin GPIO_PIN_5
#define WE_GPIO_Port GPIOB
#define RESER_Pin GPIO_PIN_6
#define RESER_GPIO_Port GPIOB
#define WP_Pin GPIO_PIN_7
#define WP_GPIO_Port GPIOB
#define RY_BY_Pin GPIO_PIN_8
#define RY_BY_GPIO_Port GPIOB
#define BYTE_Pin GPIO_PIN_9
#define BYTE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
