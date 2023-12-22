/**
  ******************************************************************************
  * @file    structures.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "structures.h"
/*----------------------------------------------------------------------------*/
global_settings SETTINGS;
action_settings ACTION[4][30];                             // array for some actions. 1 is writing actions, 2 is reading actions, 3 is erasing actions
/*----------------------------------------------------------------------------*/
uint8_t  maxAction[4] = {0,0,0};                           // the action number that is currently in use
uint32_t dataTest = 0xAA;
/*----------------------------------------------------------------------------*/
