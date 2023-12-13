/**
  ******************************************************************************
  * @file    cmd_JSON.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention this library translate JSON string to commands
  ******************************************************************************
  */

#include "cmd_JSON.h"
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>
// все строки разбирать тут, в остальные функции класть только циферные значения

/*----------------------------------------------------------------------------*/
/**
 * @brief this function converts JSON string to commands and calls necessary functions
 * @param text
 */
void JSON_INPUT(char *text)
{
	char *command;
	cJSON *json = cJSON_Parse(text);
	cJSON *CMD  = cJSON_GetObjectItem(json, "COMMAND");
	command = CMD -> valuestring;
	/*----------------------------------------------------------------------------*/
	// Choosing the periphery (GPIO)
	if(strcmp(command, "INIT_GPIO") == 0)
	{
		char *mode, *cport, *ctype; uint16_t pins = 0, type = 0;
		mode  = cJSON_GetObjectItem(json, "MODE") -> valuestring;
		cport = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		pins  = cJSON_GetObjectItem(json, "PINS") -> valueint;
		ctype = cJSON_GetObjectItem(json, "TYPE") -> valuestring;
		if(strcmp(ctype, "ADDR1") == 0)
			type = 1;
		else if(strcmp(ctype, "ADDR2") == 0)
			type = 2;
		else if(strcmp(ctype, "DATA") == 0)
			type = 3;
		GPIO_TypeDef *port = port_name(cport);
		INIT_GPIO(port, mode, pins, type);
	}
	else if(strcmp(command, "MODIFIC_GPIO") == 0)
	{
		char *cport; uint8_t pins = 0, status = 0, action = 0;
		cport  = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		pins   = cJSON_GetObjectItem(json, "PINS") -> valueint;
		status = cJSON_GetObjectItem(json, "STATUS") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		GPIO_TypeDef *port = port_name(cport);
		MODIFIC_GPIO(port, pins, status, action);
	}
	else if(strcmp(command, "READ_GPIO") == 0)
	{
		char *cport; uint8_t pins = 0, action = 0;
		uint16_t status = 0;
		cport  = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		pins   = cJSON_GetObjectItem(json, "PINS") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		GPIO_TypeDef *port = port_name(cport);
		status = READ_GPIO(port, pins, action);
		// отправка данных обратно      добавить тут
	}
	/*----------------------------------------------------------------------------*/
	// Timer (пока не работает)
	else if(strcmp(command, "INIT_TIMER") == 0)
	{
		uint8_t number = 0, channel = 0, fill_factor = 0; uint32_t freq = 0;
		number  = cJSON_GetObjectItem(json, "NUMBER") -> valueint;
		channel = cJSON_GetObjectItem(json, "CHANNEL") -> valueint;
		freq    = cJSON_GetObjectItem(json, "FREQ") -> valueint;
		fill_factor = cJSON_GetObjectItem(json, "FILL_FACTOR") -> valueint;
		INIT_TIMER(number, channel, freq, fill_factor);
	}
	/*----------------------------------------------------------------------------*/
	// SPI
	else if(strcmp(command, "INIT_SPI") == 0)
	{
		uint8_t number = cJSON_GetObjectItem(json, "NUMBER") -> valueint;
		INIT_SPI(number);
	}
	else if(strcmp(command, "SPI_TRANSMIT") == 0)
	{
		uint8_t number = 0, action = 0, data = 0;
		number = cJSON_GetObjectItem(json, "NUMBER") -> valueint;
		data   = cJSON_GetObjectItem(json, "DATA") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		SPI_TRANSMIT(number, data, action);
	}
	else if(strcmp(command, "SPI_RECEIVE") == 0)
	{
		uint8_t number = 0, action = 0;
		number = cJSON_GetObjectItem(json, "NUMBER") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		SPI_RECEIVE(number, action);
	}
	/*----------------------------------------------------------------------------*/
	// system commands
	else if(strcmp(command, "WRITE") == 0)
	{
		ACTION_CYCLE(1);
	}
	else if(strcmp(command, "READ") == 0)
	{
		ACTION_CYCLE(2);
	}
	else if(strcmp(command, "ERASE") == 0)
	{
		ACTION_CYCLE(3);
	}
	else if(strcmp(command, "DELAY") == 0)
	{
		uint8_t action = 0;  uint16_t time = 0;
		time = cJSON_GetObjectItem(json, "TIME") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
//		DELAY(time, action);
	}
	else if(strcmp(command, "INFO") == 0)
	{
		SETTINGS.memorySize = cJSON_GetObjectItem(json, "MEMORY") -> valueint;
		SETTINGS.memoryStep	= cJSON_GetObjectItem(json, "STEP") -> valueint;
//		char *type;
//		type = cJSON_GetObjectItem(json, "TYPE") -> valuestring;
//		if (strcmp(type, "GPIO"))
//			SETTINGS.memoryType = GPIO_OUT;
//		else if (strcmp(type, "SPI"))
//			SETTINGS.memoryType = SPI_Tx;
//		else if (strcmp(type, "I2C"))
//			SETTINGS.memoryType = I2C_Tx;
	}
	else if(strcmp(command, "DATA_CHANGE") == 0)
	{
		uint8_t action = 0;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		ACTION[action][maxAction[action]].type = Data_change;
		maxAction[action]++;
	}


	cJSON_Delete(json);
	cJSON_Delete(CMD);
}


/*----------------------------------------------------------------------------*/
/**
 * @brief
 * @param port
 * @return a number port
 */
GPIO_TypeDef *port_name(char *port)
{
	GPIO_TypeDef *var = 0;
	if (strcmp(port, "PORTA") == 0)
		var = GPIOA;
	else if (strcmp(port, "PORTB") == 0)
		var = GPIOB;
	else if (strcmp(port, "PORTC") == 0)
		var = GPIOC;
	else if (strcmp(port, "PORTD") == 0)
		var = GPIOD;
	else if (strcmp(port, "PORTE") == 0)
		var = GPIOE;
	else if (strcmp(port, "PORTF") == 0)
		var = GPIOF;
	return var;
}
