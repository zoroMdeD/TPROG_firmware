/**
  ******************************************************************************
  * @file    cmd_Action.h	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 6, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef CMD_ACTION_INC_CMD_ACTION_H_
#define CMD_ACTION_INC_CMD_ACTION_H_

#include "main.h"
#include "structures.h"
#include "cmd_gpio.h"
#include "cmd_JSON.h"
#include "cmd_spi.h"
#include "cmd_timer.h"

/*----------------------------------------------------------------------------*/
extern global_settings SETTINGS;
extern action_settings ACTION[3][30];                      // array for some actions. 0 is reading actions, 1 is writing actions, 2 i erasing actions
/*----------------------------------------------------------------------------*/
extern uint8_t  maxAction[3];                              // the action number that is currently in use
extern uint32_t dataTest;
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
#endif /* CMD_ACTION_INC_CMD_ACTION_H_ */
