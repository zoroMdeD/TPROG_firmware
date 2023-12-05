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
 * @param type
 */
void INIT_GPIO(char *port, char *mode, uint16_t GPIO_Pin, char *type)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_TypeDef *PORT = port_name(port);                  // take port number

	// включить тактирование порта
	if (PORT == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if (PORT == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if (PORT == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else if (PORT == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	else if (PORT == GPIOE)
		__HAL_RCC_GPIOE_CLK_ENABLE();
	else if (PORT == GPIOF)
		__HAL_RCC_GPIOF_CLK_ENABLE();

	// Init GPIO
	GPIO_InitStruct.Pin = GPIO_Pin;
	if(strcmp(mode, "INPUT") == 0)
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	else if(strcmp(mode, "OUTPUT") == 0)
	{
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	}
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(PORT, &GPIO_InitStruct);

	// запись назначения данного порта в глобальную структуру (пока только адрес)
	if(strcmp(type, "ADDR1") == 0)
	{
		SETTINGS.portAddr1 = PORT;
		SETTINGS.pinsAddr1 = GPIO_Pin;
	}
	if(strcmp(type, "ADDR2") == 0)
	{
		SETTINGS.portAddr2 = PORT;
		SETTINGS.pinsAddr2 = GPIO_Pin;
	}
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param port
 * @param GPIO_Pin
 * @param status
 */
void MODIFIC_GPIO(char *port, uint16_t GPIO_Pin, uint8_t status, uint8_t action)
{
	GPIO_TypeDef *PORT = port_name(port);                  // take port number
	HAL_GPIO_WritePin(PORT, GPIO_Pin, status);
	// запись в действия, если требуется

}


/*----------------------------------------------------------------------------*/
uint16_t READ_GPIO(char *port, uint16_t GPIO_Pin, uint8_t action)
{
	uint16_t gpioRead = 0;
	GPIO_TypeDef *PORT = port_name(port);
	gpioRead = HAL_GPIO_ReadPin(PORT, GPIO_Pin);
	// отправка данных куда-нибудь
	return gpioRead;
}


/*----------------------------------------------------------------------------*/
uint16_t READ_GPIO_ALL(char *port, uint8_t action)
{
	uint16_t gpioReadAll = 0;
	GPIO_TypeDef *PORT = port_name(port);
	gpioReadAll = PORT->IDR;
	// отправка данных куда-нибудь
	return gpioReadAll;
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param port
 * @return a number port
 */
GPIO_TypeDef *port_name(char *port)
{
	GPIO_TypeDef *var = 0;
	if (strcmp(port, "PORTA") == 0)
		var = GPIOA;
	else if (strcmp(port, "PORTB") == 0)
		var = GPIOB;
	else if (strcmp(port, "PORTC") == 0)
		var = GPIOC;
	else if (strcmp(port, "PORTD") == 0)
		var = GPIOD;
	else if (strcmp(port, "PORTE") == 0)
		var = GPIOE;
	else if (strcmp(port, "PORTF") == 0)
		var = GPIOF;
	return var;
}
