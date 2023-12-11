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
uint32_t ACTION_CYCLE (uint8_t num)
{
	uint32_t status = 0;
	uint8_t  i = 0;                                         // action count

	if (SETTINGS.addrPins1 > 0)                             // если есть адресация выводов
	{
		for (uint32_t addr = 0; addr < SETTINGS.memorySize; addr += 1)
		{
			if (SETTINGS.addrPins2 > 0)                     // если используется два порта
			{
				// the address dividing for two ports. Second port may not start with 0
				uint32_t var = addr >> 16;
				uint8_t offset = __builtin_ctz(SETTINGS.addrPins2);
				var <<= offset;
				HAL_GPIO_WritePin(SETTINGS.addrPort1, SETTINGS.addrPins1, addr);         // может быть поменять на запись в регистр, чтобы сразу и старые значения затирать
				HAL_GPIO_WritePin(SETTINGS.addrPort2, SETTINGS.addrPins2, var);
			}
			else
				HAL_GPIO_WritePin(SETTINGS.addrPort1, SETTINGS.addrPins1, addr);
			/*----------------------------------------------------------------------------*/
			// action do
			for(i = 0; i < maxAction[num]; i++)
			{
				if (ACTION[num][i].type == GPIO_IN)        // чтение должно быть в массиве на все адреса памяти!!! Тут должен быть цикл
				{
					uint16_t data = READ_GPIO(ACTION[num][i].port, ACTION[num][i].pins, 0);
					if (data != dataTest) status++;        // пока буду тупо сравнивать результат чтения с тестовой записью. В идеале надо отправлять на комп
				}
				else if (ACTION[num][i].type == GPIO_OUT)
					MODIFIC_GPIO(ACTION[num][i].port, ACTION[num][i].pins, ACTION[num][i].status, 0);
				else if (ACTION[num][i].type == Delay)
					HAL_Delay(ACTION[num][i].data);
			}
			// reset address
			HAL_GPIO_WritePin(SETTINGS.addrPort1, SETTINGS.addrPins1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SETTINGS.addrPort2, SETTINGS.addrPins2, GPIO_PIN_RESET);
		}
	}
	// if using SPI or I2C ...
	else if (SETTINGS.addrPins1 == 0)
	{
		/*----------------------------------------------------------------------------*/
		// action do
		for(i = 0; i < maxAction[num]; i++)
		{
			if(ACTION[num][i].type == GPIO_OUT)
				MODIFIC_GPIO(ACTION[num][i].port, ACTION[num][i].pins, ACTION[num][i].status, 0);
			else if (ACTION[num][i].type == Delay)
				HAL_Delay(ACTION[num][i].data);
			else if(ACTION[num][i].type == SPI_Rx)
			{
				uint8_t data = SPI_RECEIVE(1, 0);          // всегда чтение только первого SPI
				if (data != dataTest) status++;
			}
			else if(ACTION[num][i].type == SPI_Tx)
				SPI_TRANSMIT(1, ACTION[num][i].data, 0);
//			else if(ACTION[num][i].type == I2C_Rx)         // доделать I2C!!!
//			{
//				uint8_t data = I2C_RECEIVE(1, 0);
//				if (data != dataTest) status++;
//			}
//			else if(ACTION[num][i].type == I2C_Tx)
//				I2C_TRANSMIT(1, ACTION[num][i].data, 0);
		}
	}
	return status;
}


/*----------------------------------------------------------------------------*/
