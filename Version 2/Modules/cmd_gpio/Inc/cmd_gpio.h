/**
  ******************************************************************************
  * @file    cmd_gpio.h	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef CMD_GPIO_INC_CMD_GPIO_H_
#define CMD_GPIO_INC_CMD_GPIO_H_

#include "main.h"
#include "structures.h"
/*----------------------------------------------------------------------------*/
extern global_settings SETTINGS;
extern action_settings ACTION[4][30];                      // array for some actions. 0 is reading actions, 1 is writing actions, 2 i erasing actions
/*----------------------------------------------------------------------------*/
extern uint8_t  maxAction[4];                              // the action number that is currently in use
extern uint32_t dataTest;
/*----------------------------------------------------------------------------*/
void INIT_GPIO(GPIO_TypeDef *port, char *mode, uint16_t GPIO_Pin, uint8_t type);
void MODIFIC_GPIO(GPIO_TypeDef *port, uint16_t GPIO_Pin, uint8_t status, uint8_t setAction);
uint16_t READ_GPIO(GPIO_TypeDef *port, uint16_t GPIO_Pin, uint8_t setAction);
/*----------------------------------------------------------------------------*/
#endif /* CMD_GPIO_INC_CMD_GPIO_H_ */
