#ifndef _SPI_H
#define _SPI_H

#include "main.h"

#define init_good (0)
#define no_errors (0)
#define SPI_error (0)
#define illegal_clockfreq (0x0F)
#define timeout_error (0x80)

uint8_t SPI_Master_Init(uint8_t clock_rate);
uint8_t SPI_Transfer(uint8_t send_value, uint8_t *received_value);

#endif 