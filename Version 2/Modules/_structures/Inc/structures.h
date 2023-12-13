/**
  ******************************************************************************
  * @file    structures.h	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef STRUCTURES_INC_STRUCTURES_H_
#define STRUCTURES_INC_STRUCTURES_H_

#include "main.h"

/*----------------------------------------------------------------------------*/
/**
 * @brief тип данных для типа действия. Тип действия определяет перифирию, действие с которой будет происходить
 */
typedef enum
{
	GPIO_IN  = 1,
	GPIO_OUT = 2,
	SPI_Rx   = 3,
	SPI_Tx   = 4,
	I2C_Rx   = 5,
	I2C_Tx   = 6,
	Timer    = 7,
	Delay    = 8,
	Data_change = 9
} action_type;

/*----------------------------------------------------------------------------*/
typedef struct
{
	uint32_t       memorySize;
	uint8_t        memoryStep;
	GPIO_TypeDef  *addrPort1;
	GPIO_TypeDef  *addrPort2;
	uint16_t       addrPins1;
	uint16_t       addrPins2;
	GPIO_TypeDef  *dataPort;
	uint16_t       dataPins;
} global_settings;

/*----------------------------------------------------------------------------*/
typedef struct
{
	action_type    type;
	GPIO_TypeDef  *port;
	uint16_t       pins;
	uint16_t       status;
	uint16_t       data;
} action_settings;


#endif /* STRUCTURES_INC_STRUCTURES_H_ */
