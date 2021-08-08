/*
 *   module : lcd.h
 *   Author: Khaled Ramadan
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include"config.h"
#include "common_macros.h"

/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD HW Pins */
#define CONTROLL_PORT_DIR TRISB
#define CONTROLL_PORT_OUT PORTB
#define RS p3
#define RW p4
#define E p5
#define DATA_PORT_DIR TRISC
#define DATA_PORT_out PORTC

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80


void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const uint8 *str);
void LCD_goToRowColumn(uint8 row , uint8 col);
void LCD_displayStringRowColumn(uint8 row , uint8 col , const uint8 *str);
void LCD_clearScreen(void);


#endif /* LCD_H_ */
