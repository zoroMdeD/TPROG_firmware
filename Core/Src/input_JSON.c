/*
 * input_JSON.c
 *
 * В файле находятся функции для разбора json строки\структуры и запись этих значений в массивы или переменные.
 * Еще тут инициализируются порты адреса
 *
 *  Created on: Apr 15, 2022
 *      Author: nchernov
 */

#include "main.h"
#include "cJSON.h"
#include "input_JSON.h"
#include <string.h>


/******************************************************************************************************/
// Функция разбора полученной строки, смотрит тип команды и пересылает в соответсвующую ф-цию
void json_input(char *text)
{
	cJSON *json = cJSON_Parse(text);
	cJSON *CMD =  cJSON_GetObjectItem(json, "CMD");
	cmd = CMD -> valuestring;

	// выбор необходимой функции из всех доступных
	if (strcmp(cmd, "GPIO") == 0)
		gpio_analysis(text);
//	else if (strcmp(cmd, "INFO") == 0)
//		memory_size(text);
//	else if (strcmp(cmd, "READ_ACTION") == 0)
//		parseControlRead(text);
//	else if (strcmp(cmd, "WRITE_ACTION") == 0)
//		parseControlWrite(text);
//	else if (strcmp(cmd, "ERASE_ACTION") == 0)
//		parseControlErase(text);
//    // функции чтения, записи и стирания
//	else if (strcmp(cmd, "READ") == 0)
//		read_all_memory();
//	else if (strcmp(cmd, "WRITE") == 0)
//		write_memory(0xAA);
//	else if (strcmp(cmd, "ERASE") == 0)
//		erase_memory();

	cJSON_Delete(json);
	cJSON_Delete(CMD);
}

/******************************************************************************************************/
// Функция инициализирует выводы и записывает их в соответсвующие переменные
// принимает адресные пины, пины данных и пины контроля (каждый пункт отдельной командой)
void gpio_analysis(char *text)
{
	cJSON *json = cJSON_Parse(text);
	cJSON *Port;
	cJSON *Pins;

	cJSON *Func = cJSON_GetObjectItem(json, "FUNC");
	buf = Func -> valuestring;

	Port = cJSON_GetObjectItem(json, "PORT1");                   // получение названия порта1
	port1 = Port -> valuestring;
	Pins = cJSON_GetObjectItem(json, "PINS1");                   // получение номеров выводов1
	pins1 = Pins -> valuestring;
	Port = cJSON_GetObjectItem(json, "PORT2");                   // получение названия порта2
	port2 = Port -> valuestring;
	Pins = cJSON_GetObjectItem(json, "PINS2");                   // получение номеров выводов2
	pins2 = Pins -> valuestring;

	// разбор, для какой задачи были получены порт и выводы
	if (strcmp(buf, "ADDR") == 0)
	{
		addr_Port1 = port_selection(port1);
		addr_Pins1 = parseValue(pins1);
		addr_Port2 = port_selection(port2);
		addr_Pins2 = parseValue(pins2);

		gpio_init(addr_Port1, addr_Pins1, 1);
		gpio_init(addr_Port2, addr_Pins2, 1);
	}
}
