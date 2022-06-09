/*
 * input_JSON.c
 *
 * В файле находятся функции для разбора json строки\структуры и запись этих значений в массивы или переменные.
 *
 *  Created on: Apr 15, 2022
 *      Author: nchernov
 */

#include "main.h"
#include "cJSON.h"
#include "input_JSON.h"
#include <string.h>
#include "command.h"

// создание структур массивов для хранения порядка действий
action actionRead;
action actionWrite;
action actionErase;

// переменные по сути буфер
char *cmd;
char *port1;
char *pins1;
char *port2;
char *pins2;
char *buf;

// переменные для хранения номеров адресных пинов (адрес может быть на нескольких портах)
GPIO_TypeDef *addr_Port1 = 0;
uint32_t      addr_Pins1 = 0;
GPIO_TypeDef *addr_Port2 = 0;
uint32_t      addr_Pins2 = 0;

// переменные для хранения номеров data пинов
GPIO_TypeDef *data_Port;
uint32_t      data_Pins;

// переменные для хранения номеров control пинов
GPIO_TypeDef *ctrl_Port;
uint32_t      ctrl_Pins;

// структура для конфигурации выводов
GPIO_InitTypeDef GPIO_InitStruct = {0};

// переменная для хранения объема памяти и количества команд при действиях read, write и erase
uint64_t memory = 0;
uint8_t  read_num_action  = 0;
uint8_t  write_num_action = 0;
uint8_t  erase_num_action = 0;
uint8_t  value_delay = 0;                  // задержка в микросекундах


/******************************************************************************************************/
// Функция разбора полученной строки, смотрит тип команды и пересылает в соответсвующую ф-цию
void json_input(char *text)
{
	cJSON *json = cJSON_Parse(text);
	cJSON *CMD  = cJSON_GetObjectItem(json, "CMD");
	cmd = CMD -> valuestring;

	// выбор необходимой функции из всех доступных
	if (strcmp(cmd, "GPIO") == 0)
		gpio_analysis(text);
	else if (strcmp(cmd, "INFO") == 0)
		info_analysis(text);
	else if (strcmp(cmd, "READ_ACTION") == 0)
		parseControlRead(text);
	else if (strcmp(cmd, "WRITE_ACTION") == 0)
		parseControlWrite(text);
	else if (strcmp(cmd, "ERASE_ACTION") == 0)
		parseControlErase(text);
    // функции чтения, записи и стирания
	else if (strcmp(cmd, "READ") == 0)
		read_all_memory();
	else if (strcmp(cmd, "WRITE") == 0)
		write_memory();
//	else if (strcmp(cmd, "ERASE") == 0)
//		erase_memory();

	cJSON_Delete(json);
	free(CMD);
}

/******************************************************************************************************/
// Функция инициализирует выводы и записывает их в соответсвующие переменные
// принимает адресные пины, пины данных и пины контроля (каждый пункт отдельной командой)
void gpio_analysis(char *text)
{
	cJSON *Port;
	cJSON *Pins;

	cJSON *json = cJSON_Parse(text);
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
		addr_Port1 = port_selection(port1);                      // преобразование символа значения порта в цифровое значение
		addr_Pins1 = parseValue(pins1);
		addr_Port2 = port_selection(port2);
		addr_Pins2 = parseValue(pins2);

		gpio_init(addr_Port1, addr_Pins1, 1);                    // инициализация пинов как выход
		gpio_init(addr_Port2, addr_Pins2, 1);
	}
	else if (strcmp(buf, "DATA") == 0)
	{
		data_Port = port_selection(port1);
		data_Pins = parseValue(pins1);
	}
	else if (strcmp(buf, "CONTROL") == 0)
	{
		ctrl_Port = port_selection(port1);
		ctrl_Pins = parseValue(pins1);

		gpio_init(ctrl_Port, ctrl_Pins, 1);
	}
	cJSON_Delete(json);
	free(Port);
	free(Pins);
	free(Func);

}

/******************************************************************************************************/
// Функция дешифрует размер памяти микросхемы, указаный в формате 0xFFFFF
void info_analysis(char *text)
{
	char *mem = 0;                                      // переменная для временного хранения
	memory = 0;                                         // обнуление предыдущего значения

	cJSON *json = cJSON_Parse(text);
	// получение объема памяти в HEX формате
	cJSON *MEMORY = cJSON_GetObjectItem(json, "MEMORY");
	mem = MEMORY -> valuestring;

	//удаление приписки 0x
	if (*mem == '0') mem++;
	if (*mem == 'x') mem++;

	// посимвольный перевод значения из char в int в 16-ти системе
	uint32_t size_mem = strlen(mem);                    // хз почему, но подстановка в цикл strlen не работает
	for (unsigned i = 0; i < size_mem; i++)             // цикл для опознования 16ти цифр
	{
		if (*mem>='0' && *mem<='9')      memory +=(*mem)-'0';
		else if (*mem>='A' && *mem<='F') memory +=10+(*mem)-'A';
		else if (*mem>='a' && *mem<='f') memory +=10+(*mem)-'a';
		memory = memory << 4;
		mem++;                                          // затирание первого символа
	}

	// парсер количества действий, необходиных для одноименных операций
	cJSON *READ_NUM_ACTION = cJSON_GetObjectItem(json, "READ");
	buf = READ_NUM_ACTION -> valuestring;
	read_num_action = char_to_int (buf);

	cJSON *WRITE_NUM_ACTION = cJSON_GetObjectItem(json, "WRITE");
	buf = WRITE_NUM_ACTION -> valuestring;
	write_num_action = char_to_int (buf);

	cJSON *ERASE_NUM_ACTION = cJSON_GetObjectItem(json, "ERASE");
	buf = ERASE_NUM_ACTION -> valuestring;
	erase_num_action = char_to_int (buf);

	cJSON *DELAY_US = cJSON_GetObjectItem(json, "DELAY");
	buf = DELAY_US -> valuestring;
	value_delay  = char_to_int (buf);

	cJSON_Delete(json);
	free(MEMORY);
	free(READ_NUM_ACTION);
	free(WRITE_NUM_ACTION);
	free(ERASE_NUM_ACTION);
	free(DELAY_US);
}


/******************************************************************************************************/
// Функция заполняет структуры действий (порядок действия при чтении)
// нюанс: если действие это READ, WRITE или ERASE, ф-ция не найдет соответсвующее значение и просто запишет 100 в actionRead.action [i][0]
void parseControlRead (char *text)
{
	cJSON *json = cJSON_Parse(text);
	// Нужно каждый цикл менять последнюю цифру в слове Action
	char act[9] = {'A','c','t','i','o','n','0'};

	cJSON *Port;          // переменная для записи в нулевой элемент структуры action [x][0]
	cJSON *Number;        // переменная для записи в первый элемент структуры  action [x][1]
	cJSON *Status;        // переменная для записи в второй элемент структуры  action [x][2]

	// разбираем все действия, каждый цикл - следующий action
	for (uint8_t i = 0; i < read_num_action; i++)
	{
		// преобразование строки, содержащий строку action, заменяется последний символ в строке (+49 это перевод в символы)
		if (i < 9)	act[6] = i + '1';                                   // если номер действия это одно число
		else
		{
			act[6] = (i + 1) / 10 + '0';                                // запись количества десятков
			act[7] = (i + 1) - 10 + '0';                                // запись единиц
			act[8] = 0;                                                 // запись 0 в конец строки, чтобы мк понял, что это конец строки (длина строки динамичная)
		}

		// сформировав следующую по счету строку ActionN вынимаем из строки значение порта, номера вывода и его состояние
		Port = cJSON_GetObjectItem(cJSON_GetObjectItem(json, (const char*)act), "PORT");
		port1 = Port -> valuestring;
		actionRead.action [i][0] = port_selection(port1);

		Number = cJSON_GetObjectItem(cJSON_GetObjectItem(json, (const char*)act), "NUMBER");
		buf = Number -> valuestring;
		actionRead.action [i][1] = parseValue(buf);

		Status = cJSON_GetObjectItem(cJSON_GetObjectItem(json, (const char*)act), "STATUS");
		buf = Status -> valuestring;
		// Обработка строки со словом LOW или HIGH в цифровое значение (0 или 1)
		if (strcmp(buf, "Low") == 0)        actionRead.action [i][2] = 0;
		else if (strcmp(buf, "High") == 0)  actionRead.action [i][2] = 1;
		else if (strcmp(buf, "Read") == 0)  actionRead.action [i][2] = "Read"; // тут странно, сразу просто запись не работает, возможно прикол в типе данных (а в чем еще может быть)
	}

	cJSON_Delete(json);
	free(Port);
	free(Number);
	free(Status);
}


/******************************************************************************************************/
// Функция заполняет структуры действий (порядок действия при записи)
void parseControlWrite (char *text)
{
	cJSON *json = cJSON_Parse(text);
	char act[9] = {'A','c','t','i','o','n','0'};

	cJSON *Port;
	cJSON *Number;
	cJSON *Status;

	for (uint8_t i = 0; i < write_num_action; i++)
	{
		if (i < 9)	act[6] = i + '1';
		else
		{
			act[6] = (i + 1) / 10 + '0'; act[7] = (i + 1) - 10 + '0'; act[8] = 0;
		}

		Port = cJSON_GetObjectItem(cJSON_GetObjectItem(json, act), "PORT");
		port1 = Port -> valuestring;
		actionWrite.action [i][0] = port_selection(port1);

		Number = cJSON_GetObjectItem(cJSON_GetObjectItem(json, act), "NUMBER");
		buf = Number -> valuestring;
		actionWrite.action [i][1] = parseValue(buf);

		Status = cJSON_GetObjectItem(cJSON_GetObjectItem(json, act), "STATUS");
		buf = Status -> valuestring;

		Status = cJSON_GetObjectItem(cJSON_GetObjectItem(json, (const char*)act), "STATUS");
		buf = Status -> valuestring;
		if (strcmp(buf, "Low") == 0)          actionWrite.action [i][2] = 0;
		else if (strcmp(buf, "High") == 0)    actionWrite.action [i][2] = 1;
		else if (strcmp(buf, "Write") == 0)   actionWrite.action [i][2] = "Write";
	}
	cJSON_Delete(json);
	free(Port);
	free(Number);
	free(Status);
}


/******************************************************************************************************/
// Функция заполняет структуры действий (порядок действия при записи)
void parseControlErase (char *text)  // еще не проверял, но это чисто копия write и read
{
	cJSON *json = cJSON_Parse(text);
	char act[9] = {'A','c','t','i','o','n','0'};

	cJSON *Port;
	cJSON *Number;
	cJSON *Status;

	for (uint8_t i = 0; i < erase_num_action; i++)
	{
		if (i < 9)	act[6] = i + '1';
		else
		{
			act[6] = (i + 1) / 10 + '0'; act[7] = (i + 1) - 10 + '0'; act[8] = 0;
		}

		Port = cJSON_GetObjectItem(cJSON_GetObjectItem(json, act), "PORT");
		port1 = Port -> valuestring;
		actionErase.action [i][0] = port_selection(port1);

		Number = cJSON_GetObjectItem(cJSON_GetObjectItem(json, act), "NUMBER");
		buf = Number -> valuestring;
		actionErase.action [i][1] = parseValue(buf);

		Status = cJSON_GetObjectItem(cJSON_GetObjectItem(json, act), "STATUS");
		buf = Status -> valuestring;

		if (strcmp(buf, "Low") == 0)       actionErase.action [i][2] = 0;
		else if (strcmp(buf, "High") == 0) actionErase.action [i][2] = 1;
	}
	cJSON_Delete(json);
	free(Port);
	free(Number);
	free(Status);
}


/******************************************************************************************************/
// Функция разбора подстроки значений параметра, принимает указатель на массив символов со значениями параметра
uint32_t parseValue(char *value)
{
	uint32_t tmp = 0;
	uint32_t size = strlen(value);
	uint8_t j = size/2 - 1;

	for(int i = 0; i < size; i++)                              // счетчик j нужен для записи битов в обратном порядке
	{
		if (value[i] == '1')
		{
			tmp += (1 << j);                                   // сдвиг бита в соответсвующую ему позицию
			j--;
		}

		if (value[i] == '0')
			j--;
	}
	return tmp;
}


/******************************************************************************************************/
// Посимвольный перевод значения из char в int (работает только с десятичной системой счисления). Универсален
uint8_t char_to_int (char *text)
{
	uint8_t data = 0;
	uint8_t data_buf = 0;
	uint8_t size_text = strlen(text);
	for (unsigned i = size_text; i > 0; i--)
	{
		data_buf = (*text) - '0';                        // преобразование символа в цифру
		for (unsigned j = (i - 1); j > 0; j--)
			data_buf *= 10;                              // это вместо 10^i
		data += data_buf;
		text++;                                          // затирание первого символа
	}
	return data;
}
