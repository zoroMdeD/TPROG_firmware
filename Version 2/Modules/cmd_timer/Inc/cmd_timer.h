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
extern active_read     ACTIVE_READ;
extern active_write    ACTIVE_WRITE;
extern active_erase    ACTIVE_ERASE;
/*----------------------------------------------------------------------------*/
void INIT_TIMER(uint8_t number, uint8_t channel, uint32_t freq, uint8_t fill_factor);
/*----------------------------------------------------------------------------*/
#endif /* CMD_TIMER_INC_CMD_TIMER_H_ */
