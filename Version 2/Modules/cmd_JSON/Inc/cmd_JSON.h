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
#include "cmd_gpio.h"
#include "cmd_timer.h"
/*----------------------------------------------------------------------------*/
void JSON_INPUT(char *text);
void JSON_GPIO_INIT(void);

#endif /* CMD_JSON_INC_CMD_JSON_H_ */
