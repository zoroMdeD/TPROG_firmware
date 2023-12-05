/**
  ******************************************************************************
  * @file    cmd_JSON.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 4, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "cmd_JSON.h"
#include "cJSON.h"
#include <string.h>
#include <stdlib.h>


/*----------------------------------------------------------------------------*/
void JSON_INPUT(char *text)
{
	char *command;
	cJSON *json = cJSON_Parse(text);
	cJSON *CMD  = cJSON_GetObjectItem(json, "COMMAND");
	command = CMD -> valuestring;

	// Choosing the periphery (GPIO)
	if(strcmp(command, "INIT_GPIO") == 0)
	{
		char *mode, *port, *type; uint8_t pins;
		mode = cJSON_GetObjectItem(json, "MODE") -> valuestring;
		port = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		pins = cJSON_GetObjectItem(json, "PINS") -> valueint;
		type = cJSON_GetObjectItem(json, "TYPE") -> valuestring;
		INIT_GPIO(port, mode, pins, type);
	}
	else if(strcmp(command, "MODIFIC_GPIO") == 0)
	{
		char *port; uint8_t pins, status, action;
		port = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		pins = cJSON_GetObjectItem(json, "PINS") -> valueint;
		status = cJSON_GetObjectItem(json, "STATUS") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		MODIFIC_GPIO(port, pins, status, action);
	}
	else if(strcmp(command, "READ_GPIO") == 0)
	{
		char *port; uint8_t pins, action;
		uint16_t status = 0;
		port = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		pins = cJSON_GetObjectItem(json, "PINS") -> valueint;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		status = READ_GPIO(port, pins, action);
		// отправка данных обратно      добавить тут
	}
	else if(strcmp(command, "READ_GPIO_ALL") == 0)
	{
		char *port; uint8_t action;
		uint16_t status = 0;
		port = cJSON_GetObjectItem(json, "PORT") -> valuestring;
		action = cJSON_GetObjectItem(json, "ACTION") -> valueint;
		status = READ_GPIO_ALL(port, action);
		// отправка данных обратно      добавить тут
	}
	// Timer
	else if(strcmp(command, "INIT_TIMER") == 0)
	{
		uint8_t number, channel, fill_factor; uint32_t freq;
		number = cJSON_GetObjectItem(json, "NUMBER") -> valueint;
		channel = cJSON_GetObjectItem(json, "CHANNEL") -> valueint;
		freq = cJSON_GetObjectItem(json, "FREQ") -> valueint;
		fill_factor = cJSON_GetObjectItem(json, "FILL_FACTOR") -> valueint;
		INIT_TIMER(number, channel, freq, fill_factor);
	}

	cJSON_Delete(json);
	cJSON_Delete(CMD);
}



