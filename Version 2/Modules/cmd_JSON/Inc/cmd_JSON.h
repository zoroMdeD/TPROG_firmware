/**
  ******************************************************************************
  * @file    cmd_JSON.h	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef CMD_JSON_INC_CMD_JSON_H_
#define CMD_JSON_INC_CMD_JSON_H_

#include "main.h"
#include "cmd_Action.h"
#include "cmd_gpio.h"
#include "cmd_spi.h"
#include "cmd_timer.h"
/*----------------------------------------------------------------------------*/
extern global_settings SETTINGS;
extern action_settings ACTION[3][30];                      // array for some actions. 0 is reading actions, 1 is writing actions, 2 i erasing actions
/*----------------------------------------------------------------------------*/
extern uint8_t  countAction[3];                            // the action number that is currently in use
extern uint8_t  maxAction[3];                              // max actions value
extern uint32_t dataTest;
/*----------------------------------------------------------------------------*/
void JSON_INPUT(char *text);
void JSON_GPIO_INIT(void);
GPIO_TypeDef *port_name(char *port);
/*----------------------------------------------------------------------------*/
#endif /* CMD_JSON_INC_CMD_JSON_H_ */
