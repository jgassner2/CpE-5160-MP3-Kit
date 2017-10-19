#ifndef _UART_H
#define _UART_H
#include "main.h"

#define SMOD1 (0)
#define SPD (1)
#define BAUD_RATE (9600)
#define BRL_value ((uint8_t)(256-(((1+(5*SPD))*(1+(1*SMOD1))*OSC_FREQ)/(32*OSC_PER_INST*(uint32_t)BAUD_RATE))))
#define Fper (OSC_FREQ*6/OSC_PER_INST)
#define TH1 (uint8_t)(256-(((1+(1*SMOD1))*OSC_FREQ)/(32*OSC_PER_INST*(uint32_t)*BAUD_RATE)))

// ASCII characters
#define space (0x20)
#define CR (0x0D)
#define LF (0x0A)
#define BS (0x08)
#define DEL (0x7F)

void UART_Init(void);
uint8_t UART_Transmit(uint8_t send_value);
uint8_t UART_Receive(void);

#endif
