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
active_read     ACTIVE_READ[30];                           // по 30ть действий в каждом
active_write    ACTIVE_WRITE[30];
active_erase    ACTIVE_ERASE[30];
uint8_t valueRead = 0, valueWrite = 0, valueErase = 0;
uint8_t countRear = 0, countWrite = 0, countErase = 0;
/*----------------------------------------------------------------------------*/
