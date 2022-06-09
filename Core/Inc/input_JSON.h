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
	// 32 - макс. количество действий, 3 это описания действия: порт, вывод, его состояние или общее действие, типа read\write
	uint32_t action [32][3];
} action;

void json_input(char *text);
void gpio_analysis(char *text);
void info_analysis(char *text);
void parseControlRead(char *text);
void parseControlWrite(char *text);
void parseControlErase(char *text);

uint32_t parseValue(char *value);
uint8_t char_to_int(char *text);

#endif /* INC_INPUT_JSON_H_ */
