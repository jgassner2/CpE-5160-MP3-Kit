#include "main.h"
#include "LCD.h"
#include "port.h"
#include "hardware_delay_TO_ms.h"




void LCD_Write(bit RS_value, uint8_t Data_value) {
	RS = RS_value;
	E = 1;
	LCD_Port = Data_value;
	E = 0;
	LCD_Port = 0xFF;
}


void LCD_Init() {
	LCD_Write(RS_Low, function_set);
	hardware_delay(30);
	LCD_Write(RS_Low, function_set);
	hardware_delay(5);
	LCD_Write(RS_Low, function_set);
	hardware_delay(1);
	LCD_Write(RS_Low, function_set);
	hardware_delay(1);
	LCD_Write(RS_Low, display_on);
	hardware_delay(1);
	LCD_Write(RS_Low, display_clear);
	hardware_delay(1);
	LCD_Write(RS_Low, dec_mode);
}

void LCD_Output_Display(uint8_t num_bytes, uint8_t *array) {
	uint8_t index;
	for(index = 0; index < num_bytes; index++) {
		LCD_Write(1, *(array + index));
	}
}

