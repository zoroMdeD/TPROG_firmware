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
extern action_settings ACTION[3][30];                      // array for some actions. 0 is reading actions, 1 is writing actions, 2 i erasing actions
/*----------------------------------------------------------------------------*/
extern uint8_t  countAction[3];                            // the action number that is currently in use
extern uint8_t  maxAction[3];                              // max actions value
extern uint32_t dataTest;
/*----------------------------------------------------------------------------*/
void INIT_TIMER(uint8_t number, uint8_t channel, uint32_t freq, uint8_t fill_factor);
/*----------------------------------------------------------------------------*/
#endif /* CMD_TIMER_INC_CMD_TIMER_H_ */
