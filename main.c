//This is the main program file for CpE5160
//Project Members: Jonathan Gassner and Addis Greene

#include <stdio.h>
#include "uart.h"
#include "print_bytes.h"
#include "port.h"
#include "hardware_delay_TO_ms.h"
#include "LCD.h"


uint8_t temp_char;
uint8_t code LCD_string1[]="Jonathan Gassner";
uint8_t code LCD_string2[]="Addis Greene";

void main(void) {
	//Commenting out for troubleshooting
	
//		uint8_t * codememory_ptr;
//		uint8_t * xdatamemory_ptr;
	  
/*
		AUXR = 0x0C;

	//Below deals with the CKCOND register.  Need to see if this goes here or somewhere else.
		if(OSC_PER_INST == 6)
			{CKCON0 = 0x01;}
		else
			if(OSC_PER_INST == 12)
				 {CKCON0 = 0x00;}
*/
	//Visual representation of program working

  	REDLED = 0;
		hardware_delay(500);
		YELLOWLED = 0;
		hardware_delay(500);
		AMBERLED = 0;
		hardware_delay(500);
		GREENLED = 0;
		hardware_delay(500);
		
		REDLED = 1;
		hardware_delay(500);
		YELLOWLED = 1;
		hardware_delay(500);
		AMBERLED = 1;
		hardware_delay(500);
		GREENLED = 1;
		hardware_delay(500);



	//UART Initialization
		UART_Init();
		hardware_delay(100);
	
  //Pointer section.  Having compiling issues with conversion	
  //codememory_ptr = code_memory_init();
  //xdatamemory_ptr = xdatamemory_ptr();
	
	//Prints memory block to UART.  Not working at the moment.
	//print_memory(codememory_ptr, 41);
	//print_memory(xdatamemory_ptr, 42);
/*
  //LCD routine
  LCD_Init();
	LCD_Write(1, set_address | line2);
	LCD_Output_Display(10, LCD_string1);
	hardware_delay(1);
	LCD_Write(1, set_address | line2);
	LCD_Output_Display(11, LCD_string2);
*/	
  while (1)
  {
    //Testing code for echoing UART
    
		//UART_Receive();
    //UART_Transmit('u');
		putchar('u');
		hardware_delay (100);
    	

  }  //End while
	
}