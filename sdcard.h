#ifndef _SDCARD_H
#define _SDCARD_H
#include "main.h"

#define no_errors (0)
#define timeout_error (0x81)
#define illegal_command (0x82)
#define response_error (0x83)
#define data_error (0x84)
#define voltage_error (0x85)
#define card_inactive (0x86)
#define SPI_error (0x87)

#define unknown (0xFF)
#define Ver2 (0x02)
#define Standard_Capacity (9)
#define High_Capacity (0)

#define CMD0 (0)
#define CMD8 (8)
#define CMD16 (16)
#define CMD17 (17)
#define CMD55 (55)
#define CMD58 (58)
#define ACMD41 (41)
uint8_t send_command(uint8_t command, uint32_t argument);
uint8_t receive_response(uint8_t numBytes, uint8_t * arrayName);
uint8_t SD_Card_Init(void);
uint8_t read_block(uint16_t numBytes, uint8_t * array);
uint8_t Return_SD_Card_Type(void);
void print_error(uint8_t error);

#endif