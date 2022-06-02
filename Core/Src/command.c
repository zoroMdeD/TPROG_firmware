/*
 * command.c
 *
 * В файле представлены функции, которые, опираясь на записанные в массивы и переменные данные производят проверку микросхемы
 *
 *  Created on: Apr 26, 2022
 *      Author: nchernov
 */

#include "main.h"
#include <string.h>
#include "input_JSON.h"
#include "command.h"
#include "usb_device.h"
#include "delay_micros.h"

// переменная для отсчета десятков микросекунд
volatile uint32_t time_us = 0;

// максимальное значение адреса
uint32_t addr_max = 0;
// начальный пин второго адресного порта
uint16_t addr_port2_num = 0;
// кол-во aдресных пинов
uint8_t  addr_quantity_pins = 0;

extern TIM_HandleTypeDef htim1;

// структура для конфигурации выводов
extern GPIO_InitTypeDef GPIO_InitStruct;
extern GPIO_TypeDef *addr_Port1, *data_Port, *addr_Port2;
extern uint32_t addr_Pins1, data_Pins, addr_Pins2;

extern action actionRead;
extern action actionWrite;
extern action actionErase;

extern uint64_t memory;
extern uint8_t  read_num_action;
extern uint8_t  write_num_action;
extern uint8_t  erase_num_action;
extern uint8_t  value_delay;

/******************************************************************************************************/
// Функция читает всю микросхему и отправляет данные по USB
// функция работает так, что если есть второй порт адресных пинов, то первый порт должен использоваться от 0 до 16 вывода
// а если используется только один порт, то выводы идут по порядку с 0 (в будущем может это доработать)
// Если используется для выставления адреса второй порт, в нем выводы должны идти так же по порядку, но не обязательно с 0
void read_all_memory()
{
	uint16_t number = 0;                      // номер бита, с которого начинается отсчет второго порта адреса
	gpio_init(data_Port, data_Pins, 0);       // инициализация выводов как вход

	// вычисление максимального значения адреса
	addr_calculation ();

	// цикл, отсчитывающий адреса от 0 до максимального значения
	for (uint64_t i = 0; i < addr_max; i++)
	{
		// сброс адресных пинов в 0
		HAL_GPIO_WritePin(addr_Port1, addr_Pins1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(addr_Port2, addr_Pins2, GPIO_PIN_RESET);

		// выставление адреса на пинах
		HAL_GPIO_WritePin(addr_Port1, i & 0xFFFF, GPIO_PIN_SET);    // выставление адреса на первом порту
		if (i > 0xFFFF)
		{
			// выставление адреса на втором порте (тут сложнее, так как выводы могут быть не с 0)
			uint32_t hi_i = (i >> 16) & 0xFFFF;                     // hi_i это биты адреса для второго порта
			// сдвиг значения сост выводов пинов к пину, с которого начинается отсчет (на втором порте адрес выставляется не с 0 бита)
			HAL_GPIO_WritePin(addr_Port2, (hi_i << addr_port2_num) & 0xFFFF, GPIO_PIN_SET);
		}

		// выполнение всех действий из структуры actionRead
		for (uint8_t j = 0; j < read_num_action; j++)
		{
			if (actionRead.action[j][0] != 100)                     // если действие это переключение вывода
			{
				if (actionRead.action[j][2] == 1)
					 HAL_GPIO_WritePin((GPIO_TypeDef*)actionRead.action[j][0], actionRead.action[j][1], GPIO_PIN_SET);
				else HAL_GPIO_WritePin((GPIO_TypeDef*)actionRead.action[j][0], actionRead.action[j][1], GPIO_PIN_RESET);
			}
			else read_memory();                                     // если действие это чтение
		}
	}
}


/******************************************************************************************************/
// Функция считывает значение с data выводов, формирует строку и отправляет ее по USB
// подумать, может отправлять не каждое чтение, а сразу пачкой из нескольких?
void read_memory()
{
	delay_us(value_delay);                          // задержка
	uint32_t data = 0;                              // учесть, что дата может быть несколько портов
	data = (data_Port -> IDR) & data_Pins;          // считывает, но весь порт, поэтому через & убираем лишнее

	// отправка по USB (проверить, не будет ли резать данные при большем количестве gpio I\O (Trancmit принимает uint8_t)
	// ф-ция блокирует работу, поэтому в режиме отладки комментировать эти строки
//	while (CDC_Transmit_FS(&data, 1) != USBD_OK);   // отправка и ожидание окончания отправки
//	CDC_Transmit_FS(&data, 1);

	// проверка, правильное ли значение считывается, потом удалить
	// ранее указал, что записываться будет АА. Если все верно считывается, то горит зеленый светодиод
	if (data == 0xFF)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0 | GPIO_PIN_2, GPIO_PIN_RESET);
	}
	else if (data == 0xAA)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0 | GPIO_PIN_1, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2 | GPIO_PIN_1, GPIO_PIN_RESET);
	}
}


/******************************************************************************************************/
// Функция записывает в память 0хАА
void write_memory(uint32_t data)
{
	addr_calculation ();                      // вычисление максимального значения адреса
//	uint32_t data_write = data;               // записываемые данные
	uint32_t data_write = 0xAA;               // записываем АА во все ячейки памяти
	gpio_init(data_Port, data_Pins, 1);       // инициализация выводов как выход

	// цикл, отсчитывающий адреса до максимального значения
	for (uint64_t i = 0; i < addr_max; i++)
	{
		// сброс адресных пинов
		HAL_GPIO_WritePin(addr_Port1, addr_Pins1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(addr_Port2, addr_Pins2, GPIO_PIN_RESET);

		// выставление адреса на пинах
		HAL_GPIO_WritePin(addr_Port1, i & 0xFFFF, GPIO_PIN_SET);    // выставление адреса на первом порту
		if (i > 0xFFFF)
		{
			// выставление адреса на втором порте (тут сложнее, так как выводы могут быть не с 0)
			uint32_t hi_i = (i >> 16) & 0xFFFF;                     // hi_i это биты адреса для второго порта
			// сдвиг значения сост выводов пинов к пину, с которого начинается отсчет (на втором порте адрес выставляется не с 0 бита)
			HAL_GPIO_WritePin(addr_Port2, (hi_i << addr_port2_num) & 0xFFFF, GPIO_PIN_SET);
		}

		// выполнение всех действий из массивов
		for (uint8_t j = 0; j < write_num_action; j++)
		{
			// если действие это переключение вывода
			if (actionWrite.action[j][0] != 100)
			{
				if (actionWrite.action[j][2] == 1)
					HAL_GPIO_WritePin((GPIO_TypeDef*)actionWrite.action[j][0], actionWrite.action[j][1], GPIO_PIN_SET);
				else HAL_GPIO_WritePin((GPIO_TypeDef*)actionWrite.action[j][0], actionWrite.action[j][1], GPIO_PIN_RESET);
			}
			// если действие это запись
			else
			{
				// чтобы данные не повторялись
//				if (data_write == 0x55) data_write = 0xAA;
//				else data_write = 0x55;
				HAL_GPIO_WritePin((GPIO_TypeDef*)data_Port, data_Pins, GPIO_PIN_RESET);    // обнуление всех выводов
				HAL_GPIO_WritePin((GPIO_TypeDef*)data_Port, data_write, GPIO_PIN_SET);	   // установка данных на пины
				delay_us(value_delay);                          // задержка
			}
		}
	}
}


/******************************************************************************************************/
// Функция рассчитывает количество адрессных пинов, чтобы понять, до какого значения считать и записывает это значение в глоб перем
// также тут вычисляется значение бита, с которого начинается адрес на втором порту
void addr_calculation ()
{
	if (addr_max != 0) return;
	uint32_t addr_Pins_buf = addr_Pins1;

	while (addr_Pins_buf > 0)          // расчет количества используемых пинов в первом порте
	{
		if (addr_Pins_buf % 2 == 1)
			addr_quantity_pins++;
		addr_Pins_buf /= 2;
	}

	addr_Pins_buf = addr_Pins2;	       // расчет количества используемых пинов во втором порте
	while (addr_Pins_buf > 0)
	{
		if (addr_Pins_buf % 2 == 1)
			addr_quantity_pins++;
		addr_Pins_buf /= 2;
	}

	// теперь, зная кол-во пинов адреса, вычисляется максимальное значение адреса
	addr_max = 1;
	for (int j = 1; j <= addr_quantity_pins; j++)
	{
		addr_max *= 2;
	}

	// для выставления адреса на втором порте необходимо получить номер бита, с которого он начинается
	for (int k = 15; k > 0; k--)
	{
		// сдвигаем число, начиная со старшего бита, пока не найдется последний, содержащий единицу
		if ((addr_Pins2 >> k) == 1)
		addr_port2_num = k;
	}
}
