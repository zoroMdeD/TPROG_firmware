/*
 * sd.h
 *
 *  Created on: Jul 25, 2022
 *      Author: nchernov
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include "stm32f4xx_hal.h"

// команды SDcard
#define CMD0 (0x40+0)          // GO_IDLE_STATE
#define CMD1 (0x40+1)          // SEND_OP_COND (MMC)
#define ACMD41 (0xC0+41)       // SEND_OP_COND (SDC)
#define CMD8 (0x40+8)          // SEND_IF_COND
#define CMD9 (0x40+9)          // SEND_CSD
#define CMD16 (0x40+16)        // SET_BLOCKLEN
#define CMD17 (0x40+17)        // READ_SINGLE_BLOCK
#define CMD24 (0x40+24)        // WRITE_BLOCK
#define CMD55 (0x40+55)        // APP_CMD
#define CMD58 (0x40+58)        // READ_OCR

// Типы карт
#define CT_MMC 0x01            // MMC
#define CT_SD1 0x02            // SD версия 1
#define CT_SD2 0x04            // SD версия 2
#define CT_SDC (CT_SD1|CT_SD2) // SD
#define CT_BLOCK 0x08          // заблокированный адрес ?

// Дерганье CS
#define SD_SELECT()   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET)
#define SD_DESELECT() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET)

/******************************************************************************************************/
HAL_StatusTypeDef sd_init();
uint8_t           sd_WriteRead(uint8_t data);
uint8_t           sd_cmd(uint8_t cmd, uint32_t arg);
HAL_StatusTypeDef sd_ReadBlock  (uint8_t *data, uint32_t LBA);
HAL_StatusTypeDef sd_WriteBlock (uint8_t *data, uint32_t LBA);

/******************************************************************************************************/
// обмозговать эту шляпу
typedef struct sd_info {
	volatile uint8_t type;
} sd_info_ptr;

#endif /* INC_SD_H_ */
