/*------------------------------------------------
Main.H (v1.00)
--------------------------------------------------
Project Header for Project 1
-------------------------------------------------*/

#ifndef _MAIN_H
#define _MAIN_H

#include "AT89C51RC2.h"

#define OSC_FREQ (18432000UL)

//Number of oscillations per instruction
//12 - original 8051/8052 and numerous modern versions
// 6 - various Infineon and Philips devices, etc.
// 4 - Dallas 320, 520, etc.
// 1 - Dallas 420, etc.

#define OSC_PER_INST (6) //Working in x2 mode.  Need the speed

//Typedefs 
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;
typedef char int8_t;
typedef int int16_t;
typedef long int32_t;

//Interrupts 
#define Timer_0_Overflow 1
#define Timer_1_Overflow 3
#define Timer_2_Overflow 5

#endif

/*---------------------END OF FILE-------------------*/
