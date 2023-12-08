/**
  ******************************************************************************
  * @file    cmd_spi.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 6, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "cmd_spi.h"
/*----------------------------------------------------------------------------*/
SPI_HandleTypeDef hspi;
/*----------------------------------------------------------------------------*/
void INIT_SPI(uint8_t number)
{
	if (number == 1)
		hspi.Instance = SPI1;
	else if (number == 2)
		hspi.Instance = SPI2;
	else if (number == 3)
		hspi.Instance = SPI3;

	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi) != HAL_OK)
	{
		Error_Handler();
	}
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param number
 * @param data
 * @param setAction
 */
void SPI_TRANSMIT(uint8_t number, uint8_t data, uint8_t setAction)
{
	if(number == 1)
		hspi.Instance = SPI1;
	else if(number == 2)
		hspi.Instance = SPI2;
	else if(number == 3)
		hspi.Instance = SPI3;

	if(setAction == 0)
		HAL_SPI_Transmit(&hspi, &data, sizeof(data), 0xFFF);
	else
	{
		ACTION[setAction][countAction[setAction]].type = SPI_Tx;
		ACTION[setAction][countAction[setAction]].data = data;
		countAction[setAction]++;
	}
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param number
 * @param setAction
 * @return
 */
uint8_t SPI_RECEIVE(uint8_t number, uint8_t setAction)
{
	if(number == 1)
		hspi.Instance = SPI1;
	else if(number == 2)
		hspi.Instance = SPI2;
	else if(number == 3)
		hspi.Instance = SPI3;
	uint8_t data = 0;
	if(setAction == 0)
		HAL_SPI_Receive(&hspi, &data, 1, 0xFFF);
	else
	{
		ACTION[setAction][countAction[setAction]].type = SPI_Rx;
		ACTION[setAction][countAction[setAction]].data = data;
		countAction[setAction]++;
	}
	return data;
}
