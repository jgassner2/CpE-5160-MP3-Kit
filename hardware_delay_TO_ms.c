#include "main.h"
#include "port.h"
#include "hardware_delay_TO_ms.h"

//Fixing first

void hardware_delay(uint16_t timeout_ms) {
	//Configures Timer0 to mode 16
	uint16_t index;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	ET0 = 0;
	TR0 = 0; //This stops the timer just in case so we can preload values
	for(index=0; index < timeout_ms; index++) {
		TH0 = Preload_1ms_H;
		TL0 = Preload_1ms_L;
		TF0 = 0; //Clears overflow flag
		TR0 = 1; //Starts Timer 1
		while(TF0 == 0);  //Waits until the flag is set
		TR0 = 0;
	}
}
