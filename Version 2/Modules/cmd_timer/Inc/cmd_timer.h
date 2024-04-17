/**
  ******************************************************************************
  * @file    cmd_timer.h	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 5, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
#ifndef CMD_TIMER_INC_CMD_TIMER_H_
#define CMD_TIMER_INC_CMD_TIMER_H_

#include "main.h"
#include "structures.h"
/*----------------------------------------------------------------------------*/
extern global_settings SETTINGS;
extern action_settings ACTION[4][30];                      // array for some actions. 0 is reading actions, 1 is writing actions, 2 i erasing actions
/*----------------------------------------------------------------------------*/
extern uint8_t  maxAction[4];                              // max actions value
extern uint32_t dataTest;

extern TIM_HandleTypeDef htim14;
/*----------------------------------------------------------------------------*/
void DELAY (uint32_t time, uint8_t action);
/*----------------------------------------------------------------------------*/
#endif /* CMD_TIMER_INC_CMD_TIMER_H_ */
