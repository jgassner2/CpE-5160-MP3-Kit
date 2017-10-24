#include "main.h"
#include "SPI.h"
#include "port.h"

uint8_t SPI_Master_Init(uint32_t clock_rate) {
	uint8_t divider;
	uint8_t return_val;
	divider = (uint8_t)(((OSC_FREQ/OSC_PER_INST)*6)/clock_rate);

	if(divider <= 2)
		SPCON = 0x70;
	else if((divider > 2) && (divider <= 4))
		SPCON = 0x71;
	else if((divider > 4) && (divider <= 8))
		SPCON = 0x72;
	else if((divider > 8) && (divider <= 16))
		SPCON = 0x73;
	else if((divider > 16) && (divider <= 32))
		SPCON = 0xF0;
	else if((divider > 32) && (divider <= 64))
		SPCON = 0xF1;
	else if((divider > 64) && (divider <= 128))
		SPCON = 0xF2;
	else
		return_val = illegal_clockfreq;
	return return_val;

}

uint8_t SPI_Transfer(uint8_t send_value, uint8_t *received_value) {
	uint8_t test;
	uint8_t timeout;
	timeout = 0;
	SPDAT = send_value;

	do {
		test = SPSTA;
		timeout++;
	} while(((test&0xF0) == 0) && (timeout != 0));
	if(timeout != 0) {
		if((test&0x70) == 0) {
			*received_value = SPDAT;
			timeout = no_errors;
		} else {
			*received_value = 0xFF;
			timeout = SPI_error;
		}
	} else {
		*received_value = 0xFF;
		timeout = timeout_error;
	}

	return timeout;
}