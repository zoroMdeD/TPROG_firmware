/*
 * sd.c
 *
 *  Created on: Jul 25, 2022
 *      Author: nchernov
 *      Либа написана для работы с SPI вместе с FATFS. Чтобы подключить FATFS, необходимо дополнить ф-ции
 *      в user_diskio.c
 */
#include "sd.h"
#include "main.h"

extern SPI_HandleTypeDef hspi2;
char str1[60]={0};                     // мб это перенести куда-нибудь?
sd_info_ptr sdinfo;                    // разобраться с этими самодельными типами данных, может нафиг их

/******************************************************************************************************/
// Инициализация SD карты
HAL_StatusTypeDef sd_init()
{
	uint32_t spi_prescale;   // переменная для хранения предыдущего значения предделителя SPI
	HAL_StatusTypeDef stat;
	uint8_t ocr[4];
	uint8_t flag, cmd;

	HAL_Delay(5);                                               // пауза на инициализацию

	spi_prescale = hspi2.Init.BaudRatePrescaler;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;   // уменьшение частоты работы SPI до 164 кбит/c
	HAL_SPI_Init(&hspi2);

	SD_DESELECT();
	for(int i = 0; i < 10; i++)                                 // отправка >= 74 импульсов (80)
		stat = sd_WriteRead(0xFF);

	hspi2.Init.BaudRatePrescaler = spi_prescale;                // восстановление прежней скорости
	HAL_SPI_Init(&hspi2);

	if (sd_cmd(CMD0, 0) == 1)                                   // CMD0 (нужный ответ на эту команду = 1)
	{
		if (sd_cmd(CMD8, 0x1AA) == 1)                           // CMD8 (нужный ответ на эту команду = 1)
		{
			for (int i = 0; i < 4; i++) ocr[i] = sd_WriteRead(0xFF);
			if (ocr[2] != 0x01 && ocr[3] != 0xAA)               // проверка диапазона питания sd карты
				return HAL_ERROR;
			for (uint16_t i = 0; i < 10000; i++)                // ожидание ответа от sd карты, если ответа нету, то ошибка инициализации
			{
				flag = sd_cmd(ACMD41, 1UL << 30);               // ACMD41 (нужный ответ на эту команду = 0)
				if (flag == 0)                                  // если ответ на команду = 0, то выход из цикла
					break;
			}
			if (flag != 0) return HAL_ERROR;                    // если за 10к попыток нет ответа, то ошибка
			HAL_Delay(1);

			if (sd_cmd(CMD58, 0) == 0)                          // CMD58
			{
				for (int i = 0; i < 4; i++) ocr[i] = sd_WriteRead(0xFF);
				flag = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2; // не рассмотрены все варианты, оставить пока так
			}
		}
		else //SDv1 or MMCv3   данный участок не проверил
		{
			if (sd_cmd(ACMD41, 0) <= 1)
			{
				flag = CT_SD1;
				cmd = ACMD41;                                   // SDv1
			}
			else
			{
				flag = CT_MMC;
				cmd = CMD1;                                     // MMCv3
			}
			for (uint16_t i = 0; i < 10000; i++)                // ожидание ответа от sd карты, если ответа нету, то ошибка инициализации
			{
				flag = sd_cmd(cmd, 0);                          // ACMD41 (нужный ответ на эту команду = 0)
				if (flag == 0)                                  // если ответ на команду = 0, то выход из цикла
					break;
			}
			if (sd_cmd(CMD16, 512) != 0)                        // ??
				flag = 0;                                       // проверять на месте
		}
	}
	else return HAL_ERROR;

	return HAL_OK;
}


/******************************************************************************************************/
// Отправку на SD карту и чтение ответного байта
uint8_t sd_WriteRead(uint8_t data)
{
	HAL_StatusTypeDef res = 1;
	uint8_t receiveddata = 0;

	res = HAL_SPI_TransmitReceive(&hspi2,(uint8_t*) &data,(uint8_t*) &receiveddata,1,HAL_MAX_DELAY);
	if (res == HAL_OK) return receiveddata;
	else return res;
}


/******************************************************************************************************/
// Формирование для отправки на SD карту команды
// см. https://www.convict.lu/pdf/ProdManualSDCardv1.9.pdf страница 90  5.2.1. Command Format
// CRC по умолчанию выключены и смотряться только в нескольких командах
uint8_t sd_cmd (uint8_t cmd, uint32_t arg)
{
	uint8_t n, data;

	// Выбор SD карты. Нужны ли тут все эти дерганья и отправки единицы?
	SD_DESELECT();
	sd_WriteRead(0xFF);
	SD_SELECT();
	sd_WriteRead(0xFF);

	// если команда ACMD, то в начале необходимо отправить CMD55
	if (cmd & 0x80)
	{
		cmd &= 0x7F;
		data = sd_cmd(CMD55, 0);
		if (data > 1) return data;
	}

	// отправка команды и аргумента (4 пачки)
	sd_WriteRead(cmd);
	sd_WriteRead((uint8_t)(arg >> 24)); // Argument[31..24]  в таком порядке?
	sd_WriteRead((uint8_t)(arg >> 16)); // Argument[23..16]
	sd_WriteRead((uint8_t)(arg >> 8));  // Argument[15..8]
	sd_WriteRead((uint8_t)arg);         // Argument[7..0]

	// отправка CRC
	n = 0x01;                           // основа CRC (1 в конце)
	if (cmd == CMD0) {n = 0x95;}        // Valid CRC for CMD0(0)
	if (cmd == CMD8) {n = 0x87;}        // Valid CRC for CMD8(0x1AA)
	sd_WriteRead(n);

	n = 10; // Ожидание ответа, 10 попыток (по началу шлет 0xFF)
	do {
		data = sd_WriteRead(0xFF);
	} while ((data & 0x80) && --n);
	return data;
}


/******************************************************************************************************/
// Чтение блока. Передается команда (токен), дата, CRC
HAL_StatusTypeDef sd_ReadBlock (uint8_t *data, uint32_t LBA)  // LBA - длинна чтения
{
	uint8_t stat;
	uint16_t cnt;

	stat = sd_cmd (CMD17, LBA);
	if (stat != 0x00) return HAL_ERROR;

	do{                                                       // ждем начала блока
		stat=sd_WriteRead(0xFF);                              // гоним единицы в ожидание битов с sd карты
	cnt++;
	} while ((stat != 0xFE)&&(cnt < 0xFFFF));
	if (cnt >= 0xFFFF) return HAL_ERROR;                      // если не появился сигнал с карточки, то явно ошибка
	for (cnt = 0; cnt < 512; cnt++)
		data[cnt] = sd_WriteRead(0xFF);

	sd_WriteRead(0xFF);                                       // пропускаем CRC
	sd_WriteRead(0xFF);
}


/******************************************************************************************************/
// Запись в блок. Передается команда (токен), дата, CRC
HAL_StatusTypeDef sd_WriteBlock (uint8_t *data, uint32_t LBA)
{
	uint8_t stat;
	uint16_t cnt;

	stat = sd_cmd (CMD24, LBA);
	if (stat != 0x00) return HAL_ERROR;

	sd_WriteRead(0xFF);
	sd_WriteRead(0xFE);                                       // нахера эти два?

	for (cnt = 0; cnt < 512; cnt++)
		sd_WriteRead(data[cnt]);

	sd_WriteRead(0xFF);                                       // пропускаем CRC?
	sd_WriteRead(0xFF);

	stat = sd_WriteRead(0xFF);
	if ((stat&0x05) != 0x05) return HAL_ERROR;

	do {                                                      // ждем окончание состояния BUSY
		stat = sd_WriteRead(0xFF);
		cnt++;
	} while ((stat != 0xFF)&&(stat < 0xFFFF) );
	if (cnt>=0xFFFF) return HAL_ERROR;
	return HAL_OK;
}


