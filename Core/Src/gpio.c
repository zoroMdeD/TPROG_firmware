/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PG0 PG1 PG2 PG3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
/******************************************************************************************************/
// Функция инициализирует указаные выводы в соответсвующее состояние (тут не хватает включение RCC, оно реализовано в ф-ции *port_selection
void gpio_init(GPIO_TypeDef *port, uint32_t pins, uint8_t status)
{
	// структура для конфигурации выводов
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	HAL_GPIO_DeInit(port, pins);                                // в начале деинициализация
	if (status == 0)                                            // конфигурация как вход
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	else                                                        // конфигурация как выход
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	}
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Pin = pins;
	HAL_GPIO_Init(port, &GPIO_InitStruct);                      // инициализация
}


/******************************************************************************************************/
// Функция преобразует название порта (char)в его цифровое значение
GPIO_TypeDef *port_selection (char *text)
{
	if (strcmp(text, "PORTA") == 0)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		return GPIOA;
	}
	else if (strcmp(text, "PORTB") == 0)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		return GPIOB;
	}
	else if (strcmp(text, "PORTC") == 0)
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
		return GPIOC;
	}
	else if (strcmp(text, "PORTD") == 0)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
		return GPIOD;
	}
	else if (strcmp(text, "PORTE") == 0)
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
		return GPIOE;
	}
	else if (strcmp(text, "PORTF") == 0)
	{
		__HAL_RCC_GPIOF_CLK_ENABLE();
		return GPIOF;
	}
	else if (strcmp(text, "I2C") == 0)
	{
		return "I2C";
	}
	else if (strcmp(text, "0") == 0)
		return 0;
}



/* USER CODE END 2 */
