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
extern active_read     ACTIVE_READ;
extern active_write    ACTIVE_WRITE;
extern active_erase    ACTIVE_ERASE;
/*----------------------------------------------------------------------------*/
void INIT_GPIO(char *port, char *mode, uint16_t GPIO_Pin,char *type);
void MODIFIC_GPIO(char *port, uint16_t GPIO_Pin, uint8_t status, uint8_t action);
uint16_t READ_GPIO(char *port, uint16_t GPIO_Pin, uint8_t action);
uint16_t READ_GPIO_ALL(char *port, uint8_t action);
GPIO_TypeDef *port_name(char *port);
/*----------------------------------------------------------------------------*/
#endif /* CMD_GPIO_INC_CMD_GPIO_H_ */
