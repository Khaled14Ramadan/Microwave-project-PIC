/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Author: Khaled Ramadan
 *
 *******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef KEYPAD_H
#define KEYPAD_H


#include "std_types.h"
#include"config.h"
#include "common_macros.h"




/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_COL 3
#define N_ROW 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_DIR TRISD
#define KEYPAD_PORT_OUT PORTD
#define KEYPAD_PORT_IN PORTD


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 Key_getPressedKey(void);




#endif	/* KEYPAD_H */

