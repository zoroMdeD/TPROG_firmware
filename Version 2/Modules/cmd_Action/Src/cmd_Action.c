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
	uint32_t status = 0;                                   // error counter
	uint8_t  i = 0;                                        // action counter
	dataTest = 0xAA;
	for (uint32_t addr = 0; addr <= SETTINGS.memorySize; addr++)     // заводим цикл, который будет проходиться по всем адресам. Порт и выводы адреса храняться в общей структуре. Адресных портов может быть несколько
	{
		if (SETTINGS.addrPins1 > 0)                                  // если есть адресация выводов и микросхема работает через GPIO
		{
			if (SETTINGS.addrPins2 > 0)                                                  // если используется два порта, то значение адреса необходимо разделить на них обоих
			{
				// the address dividing for two ports. Second port may not start with 0
				uint32_t var = addr >> 16;
				uint8_t offset = __builtin_ctz(SETTINGS.addrPins2);
				var <<= offset;
				HAL_GPIO_WritePin(SETTINGS.addrPort1, addr, GPIO_PIN_SET);               // записываем в соответсвующие порты значения полученных адресов
				HAL_GPIO_WritePin(SETTINGS.addrPort2, var, GPIO_PIN_SET);                // !!!может быть поменять на запись в регистр, чтобы сразу и старые значения затирать
			}
			else
				HAL_GPIO_WritePin(SETTINGS.addrPort1, addr, GPIO_PIN_SET);               // если порт адреса всего один, то все проще простого
			/*----------------------------------------------------------------------------*/
			// action do                                                                 // выполнение действий
			for(i = 0; i < maxAction[num]; i++)
			{
				if (ACTION[num][i].type == GPIO_IN)
				{
					uint16_t data = READ_GPIO(ACTION[num][i].port, ACTION[num][i].pins, 0);
					if (data != dataTest) status++;
				}
				else if (ACTION[num][i].type == GPIO_OUT)
					MODIFIC_GPIO(ACTION[num][i].port, ACTION[num][i].pins, ACTION[num][i].status, 0);
				else if (ACTION[num][i].type == Delay)
					HAL_Delay(ACTION[num][i].data);
				else if (ACTION[num][i].type == Data_change)                             // простенький алгоритм для шахматного изменения записываемых данных
				{
					if (dataTest == 0xAA) dataTest = 0x55;
					else if (dataTest == 0x55) dataTest = 0xAA;
					if (num == 1)                                                        // если действие это запись, то тогда нужно менять и состояние выводов
					{
						HAL_GPIO_WritePin(SETTINGS.dataPort, SETTINGS.dataPins, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(SETTINGS.dataPort, dataTest, GPIO_PIN_SET);
					}
				}
			}
			// reset address
			HAL_GPIO_WritePin(SETTINGS.addrPort1, SETTINGS.addrPins1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(SETTINGS.addrPort2, SETTINGS.addrPins2, GPIO_PIN_RESET);
		}
		/*----------------------------------------------------------------------------*/
		// if using SPI or I2C ...
		else if (SETTINGS.addrPins1 == 0)
		{
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
					if (dataTest == 0xAA) dataTest = 0x55;     // шахматный порядок чет херово работает, при чтении все смещено на один байт
					else if (dataTest == 0x55) dataTest = 0xAA;
				}
				else if(ACTION[num][i].type == SPI_Tx)
				{
					SPI_TRANSMIT(1, dataTest, 0);              // либо ACTION[num][i].data
					if (dataTest == 0xAA) dataTest = 0x55;
					else if (dataTest == 0x55) dataTest = 0xAA;
				}

	//			else if(ACTION[num][i].type == I2C_Rx)         // доделать I2C!!!
	//			{
	//				uint8_t data = I2C_RECEIVE(1, 0);
	//				if (data != dataTest) status++;
	//			}
	//			else if(ACTION[num][i].type == I2C_Tx)
	//				I2C_TRANSMIT(1, ACTION[num][i].data, 0);
			}
		}
	}

	// проверка статуса ошибок после чтения
	if ((num == 2)&&(status == 0))
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET);
	}
	else if ((num == 2)&&(status != 0))
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);
	}
	if (num == 2)
		CDC_Transmit_FS(&status, 4);
	return status;
}


/*----------------------------------------------------------------------------*/
