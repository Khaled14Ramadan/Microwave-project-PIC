/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Khaled Ramadan
 *
 *******************************************************************************/

#include"keypad.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#if (N_COL==3)

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 num_button);

#elif (N_COL==4)

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 num_button);

#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 Key_getPressedKey(void)
{
	uint8 col ,row;

	for(;;)
	{
		for(col=0;col<N_COL;col++)/* loop for columns */
		{

#if (N_COL==3)/* this to do not change in bit_7 */
			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins include the row pins
			 */
			KEYPAD_PORT_DIR =( KEYPAD_PORT_DIR | 0x7F) & (~(0x10 << col));

			/*
			 * set the output pin column in this trace and enable the internal
			 * 
			 */

			KEYPAD_PORT_OUT =(KEYPAD_PORT_OUT & 0x80) | ((0x10)<<col);

#elif (N_COL==4)/* this to do on all port */
			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins include the row pins
			 */
			KEYPAD_PORT_DIR = ~(0x10 << col);

			/*
			 * clear the output pin column in this trace and enable the internal
			 * pull up resistors for the rows pins
			 */

			KEYPAD_PORT_OUT = (0x10 << col);

#endif
			for(row=0;row<N_ROW;row++)/* loop for rows */
			{

				if(BIT_IS_SET(KEYPAD_PORT_IN,row))/* if the switch is press in this row */
				{
#if (N_COL==3)
					return(Keypad_4x3_adjustSwitchNumber(row*N_COL+col+1));

#elif (N_COL==4)
					return(Keypad_4x4_adjustSwitchNumber(row*N_COL+col+1));

#endif

				}
			}
		}
	}
}


#if (N_COL==3)

static uint8 Keypad_4x3_adjustSwitchNumber(uint8 num_button)
{
	switch(num_button)
	{
	case 10 :
		return '*';
		break;

	case 11 :
		return 0 ;
		break;

	case 12 :
		return '#';
		break;

	default :
		return num_button;
		break;
	}
}


#elif (N_COL==4)

static uint8 Keypad_4x4_adjustSwitchNumber(uint8 num_button)
{
	switch(num_button)
	{

	case 1: return 7;
	break;
	case 2: return 8;
	break;
	case 3: return 9;
	break;
	case 4: return '%'; // ASCII Code of %
	break;
	case 5: return 4;
	break;
	case 6: return 5;
	break;
	case 7: return 6;
	break;
	case 8: return '*'; /* ASCII Code of '*' */
	break;
	case 9: return 1;
	break;
	case 10: return 2;
	break;
	case 11: return 3;
	break;
	case 12: return '-'; /* ASCII Code of '-' */
	break;
	case 13: return 13;  /* ASCII of Enter */
	break;
	case 14: return 0;
	break;
	case 15: return '='; /* ASCII Code of '=' */
	break;
	case 16: return '+'; /* ASCII Code of '+' */
	break;
	default: return num_button;

	}
}

#endif
