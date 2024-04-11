/**
  ******************************************************************************
  * @file    cmd_gpio.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "cmd_gpio.h"
#include <string.h>
/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param port
 * @param mode     gpio mode (input/output)
 * @param GPIO_Pin
 */
void INIT_GPIO(GPIO_TypeDef *port, char *mode, uint16_t GPIO_Pin, uint8_t type)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	// включить тактирование порта
	if (port == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if (port == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if (port == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else if (port == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	else if (port == GPIOE)
		__HAL_RCC_GPIOE_CLK_ENABLE();
	else if (port == GPIOF)
		__HAL_RCC_GPIOF_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_Pin;                        	// Init GPIO
	if(strcmp(mode, "INPUT") == 0)                          // GPIO mode
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	else if(strcmp(mode, "OUTPUT") == 0)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	}
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port, &GPIO_InitStruct);

	// work with type
	if(type == 1)
	{
		SETTINGS.addrPort1 = port;
		SETTINGS.addrPins1 = GPIO_Pin;
	}
	else if(type == 2)
	{
		SETTINGS.addrPort2 = port;
		SETTINGS.addrPins2 = GPIO_Pin;
	}
	else if(type == 3)
	{
		SETTINGS.dataPort = port;
		SETTINGS.dataPins = GPIO_Pin;
	}
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param port
 * @param GPIO_Pin
 * @param status
 * @param setAction
 */
void MODIFIC_GPIO(GPIO_TypeDef *port, uint16_t GPIO_Pin, uint8_t status, uint8_t setAction)
{
	if (setAction == 0)                                    // isn't action
		HAL_GPIO_WritePin(port, GPIO_Pin, status);
	else                                                   // is action
	{
		// пиздец запись конечно, хуй раздуплюсь в понедельник
		ACTION[setAction][maxAction[setAction]].type = GPIO_OUT;
		ACTION[setAction][maxAction[setAction]].port = port;
		ACTION[setAction][maxAction[setAction]].pins = GPIO_Pin;
		ACTION[setAction][maxAction[setAction]].status = status;
		maxAction[setAction]++;                            // up the action counter
	}
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param port
 * @param GPIO_Pin
 * @param setAction
 * @return data
 */
uint16_t READ_GPIO(GPIO_TypeDef *port, uint16_t GPIO_Pin, uint8_t setAction)
{
	uint16_t gpioRead = 0;
	if (setAction == 0)                                    // isn't action
	{
		gpioRead = (port->IDR) & GPIO_Pin;                 // read all ports data
//		gpioRead >>= __builtin_ctz(gpioRead);              // __builtin_ctz the returned quantity is 0 on the right
	}
	else                                                   // is action
	{
		ACTION[setAction][maxAction[setAction]].type = GPIO_IN;
		ACTION[setAction][maxAction[setAction]].port = port;
		ACTION[setAction][maxAction[setAction]].pins = GPIO_Pin;
		maxAction[setAction]++;                            // up the action counter
	}
	// отправка данных куда-нибудь
	return gpioRead;
}
