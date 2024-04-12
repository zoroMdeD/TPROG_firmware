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

void cleanStructures (void)
{
	// clean Action
	for (uint8_t i = 0; i < 4; i++)
	{
		for (uint8_t j = 0; j < 30; j++)
		{
			ACTION[i][j].data = 0;
			ACTION[i][j].pins = 0;
			ACTION[i][j].port = 0;
			ACTION[i][j].status = 0;
			ACTION[i][j].type = 0;
		}
	}
	SETTINGS.addrPins1 = 0;
	SETTINGS.addrPins2 = 0;
	SETTINGS.addrPort1 = 0;
	SETTINGS.addrPort2 = 0;
	SETTINGS.dataPins = 0;
	SETTINGS.dataPort = 0;
	SETTINGS.memorySize = 0;
	SETTINGS.memoryStep = 0;
	HAL_GPIO_WritePin(GPIOG, 7, GPIO_PIN_RESET);
}
