/**
  ******************************************************************************
  * @file    cmd_spi.h	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 6, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef CMD_SPI_INC_CMD_SPI_H_
#define CMD_SPI_INC_CMD_SPI_H_

#include "main.h"
#include "structures.h"
/*----------------------------------------------------------------------------*/
extern global_settings SETTINGS;
extern action_settings ACTION[4][30];                      // array for some actions. 0 is reading actions, 1 is writing actions, 2 i erasing actions
/*----------------------------------------------------------------------------*/
extern uint8_t  maxAction[4];                              // max actions value
extern uint32_t dataTest;
/*----------------------------------------------------------------------------*/
void INIT_SPI(uint8_t number);
void SPI_TRANSMIT(uint8_t number, uint8_t data, uint8_t setAction);
uint8_t SPI_RECEIVE(uint8_t number, uint8_t setAction);
/*----------------------------------------------------------------------------*/

#endif /* CMD_SPI_INC_CMD_SPI_H_ */
