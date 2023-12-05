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
	GPIO  = 1,/**< GPIO */
	SPI   = 2,/**< SPI */
	I2C   = 3,/**< I2C */
	Timer = 4 /**< Timer */
} action_type;

/*----------------------------------------------------------------------------*/
typedef struct
{
	uint32_t       memorySize;
	GPIO_TypeDef  *portAddr1;            // проверить работу указателей!
	GPIO_TypeDef  *portAddr2;
	uint16_t       pinsAddr1;
	uint16_t       pinsAddr2;
	GPIO_TypeDef  *portInput1;
	GPIO_TypeDef  *portInput2;
	uint16_t       pinsInput1;
	uint16_t       pinsInput2;
	GPIO_TypeDef  *portOutput1;
	GPIO_TypeDef  *portOutput2;
	uint16_t       pinsOutput1;
	uint16_t       pinsOutput2;
	GPIO_TypeDef  *portControl;
	uint16_t       pinsControl;
} global_settings;
/*----------------------------------------------------------------------------*/
typedef struct
{
	action_type    type;
	GPIO_TypeDef  *port;
	uint16_t       pins;
	uint16_t       status;
	uint64_t       data;               // Вот тут подумать надо будет, какого объема посылать данные!!!
} active_read;
/*----------------------------------------------------------------------------*/
typedef struct
{
	action_type    type;
	GPIO_TypeDef  *port;
	uint16_t       pins;
	uint16_t       status;
	uint64_t       data;
} active_write;
/*----------------------------------------------------------------------------*/
typedef struct
{
	action_type    type;
	GPIO_TypeDef  *port;
	uint16_t       pins;
	uint16_t       status;
	uint64_t       data;
} active_erase;

#endif /* STRUCTURES_INC_STRUCTURES_H_ */
