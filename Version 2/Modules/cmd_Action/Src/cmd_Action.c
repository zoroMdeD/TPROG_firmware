/**
  ******************************************************************************
  * @file    cmd_Action.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 6, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "cmd_Action.h"

/*----------------------------------------------------------------------------*/
uint32_t ACTION_CYCLE(uint8_t num)
{
	uint32_t data = 0;
	uint8_t  actionCount = 0;

	if(SETTINGS.addrPins1 > 0)                             // если есть адресация выводов
	{
		for(uint32_t addr = 0; addr < SETTINGS.memorySize; addr += SETTINGS.memoryStep)
		{

		}
//		HAL_GPIO_WritePin(SETTINGS.addrPort1, GPIO_Pin, PinState)
	}


	return data;
}


/*----------------------------------------------------------------------------*/
