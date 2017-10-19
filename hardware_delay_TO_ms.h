#ifndef _HARDWARE_DELAY_TO_MS
#define	_HARDWARE_DELAY_TO_MS


#include "main.h"
#include "port.h"

//Preload values
#define Preload_1ms ((uint16_t)(65536-(OSC_FREQ/(OSC_PER_INST*1020UL))))
#define Preload_1ms_H (Preload_1ms/256)  
#define Preload_1ms_L (Preload_1ms%256)


void hardware_delay(uint16_t timeout_ms);
	



#endif