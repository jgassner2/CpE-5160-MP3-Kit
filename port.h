/*-------------------------------------------------------------
Port.H (v1.00)
-------------------------------------------------------------*/

#ifndef _PORT_H
#define _PORT_H

#include "main.h"

sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;
sfr LCD_Port = 0x80;

sfr Port_1 = 0x90;
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

sfr Port_2 = 0xA0;
sbit SW1 = P2^0;
sbit SW2 = P2^1;
sbit SW3 = P2^2;
sbit SW4 = P2^3;
sbit REDLED = P2^4;
sbit YELLOWLED = P2^5;
sbit AMBERLED = P2^6;
sbit GREENLED = P2^7;

sfr Port_3 = 0xB0;
sbit per_TxD = P3^0;
sbit per_RxD = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit RS = P3^6;
sbit E = P3^7;

#endif 

/*------------ END OF FILE ---------------*/
