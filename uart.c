#include "main.h"
#include "UART.h"

void UART_Init() {
	BDRCON = 0; //Disables Baud Rate Generator first
	ES = 0;  //Disables interrupts
	
	if (SMOD1 == 0){
		PCON = PCON & 0x7F;
	}
	if (SMOD1 == 1) {
		PCON = PCON |	0x80;
	}
	SCON = 0x50;
	
	BRL = BRL_value;
	BDRCON = (0x1C | (SPD << 1));
	TI = 1;  //Make this last
}

uint8_t UART_Transit(uint8_t send_value) {
	while(TI == 0);
	SBUF = send_value;
	return 0;
}

uint8_t UART_Receive (void) {
	uint8_t received_value;
	while(RI == 0);
	received_value = SBUF;
	return received_value;
}