/*
 * input_JSON.h
 *
 *  Created on: Apr 15, 2022
 *      Author: nchernov
 */

#ifndef INC_INPUT_JSON_H_
#define INC_INPUT_JSON_H_

// создание типа данных для хранения action (порядка действий)
// структура хранит порядок действий при чтение, записи или удаление
typedef struct action
{
	// 32 - макс. количество действий, 3 описания действия: порт, вывод, его состояние или общее действие, типа read\write
	uint32_t action [32][3];
} action;

// создание структур массивов для хранения порядка действий
action actionRead;
action actionWrite;
action actionErase;

// переменные буфера
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

// переменная для хранения объема памяти и количества команд при действиях read, write и erase
uint64_t memory = 0;
uint8_t  read_num_action  = 0;
uint8_t  write_num_action = 0;
uint8_t  erase_num_action = 0;
uint8_t  delay_us = 0;                  // задержка в десятках микросекунд

void json_input();
void gpio_analysis();
void info_analysis();
void parseControlRead();
void parseControlWrite();
void parseControlErase();

uint32_t parseValue(char *value);
uint8_t char_to_int(char *text);

#endif /* INC_INPUT_JSON_H_ */
