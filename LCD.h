#ifndef _LCD_H
#define _LCD_H
#include "main.h"
#include "port.h"

#define set_address (0x80)
#define line1 (0x00)
#define line2 (0x40)
#define function_set (0x3C)

#define display_on (0x0C)
#define display_off (0x08)
#define cursor_on (0x0A)
#define blink_on (0x09)
#define display_clear (0x01)

#define dec_mode (0x06)
#define inc_mode (0x04)
#define shift_on (0x05)

#define RS_Low (0)
#define RS_High (1)
void LCD_Write(bit RS_value, uint8_t Data_value);
void LCD_Init(void);
void LCD_Output_Display(uint8_t num_bytes, uint8_t *array);

#endif