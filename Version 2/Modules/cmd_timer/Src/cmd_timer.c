/**
  ******************************************************************************
  * @file    cmd_timer.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 5, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "cmd_timer.h"


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param time
 * @param action
 */
void DELAY (uint32_t time, uint8_t action)
{
	if (action == 0)
	{
//		HAL_Delay(time);
		__HAL_TIM_SET_COUNTER(&htim14, 0);
		while(__HAL_TIM_GET_COUNTER(&htim14) < time);
	}
	else
	{
		ACTION[action][maxAction[action]].type = Delay;
		ACTION[action][maxAction[action]].port = 0;
		ACTION[action][maxAction[action]].pins = 0;
		ACTION[action][maxAction[action]].status = 0;
		ACTION[action][maxAction[action]].data = time;
		maxAction[action]++;                               // up the action counter
	}
}
