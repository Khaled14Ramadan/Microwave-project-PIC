/*
 * microwave.h
 *
 *  Created on: ???/???/????
 *      Author: khaled Ramandan
 */

#ifndef MICROWAVE_H_
#define MICROWAVE_H_

#include"keypad.h"
#include"timer1.h"
#include"lcd.h"


#define TIMER(X1 , X2 , Y1 ,Y2) 	{ \
		PORTA =(PORTA & 0xF0) | 0x01;\
		PORTC =(PORTC & 0xF0)|(X1 & 0x0F);\
		__delay_ms(2);\
\
		PORTA =(PORTA & 0xF0) | 0x02;\
		PORTC =(PORTC & 0xF0)|(X2 & 0x0F);\
		__delay_ms(2);\
\
		PORTA =(PORTA & 0xF0) | 0x04;\
		PORTC =(PORTC & 0xF0)|(Y1 & 0x0F);\
		__delay_ms(2);\
\
		PORTA =(PORTA & 0xF0) | 0x08;\
		PORTC =(PORTC & 0xF0)|(Y2 & 0x0F);\
		__delay_ms(2);\
}

/*  macro ON_HEATER
 *  Lamp is ON
 *   Heater is ON
 *   Motor is ON
 *
 */
#define ON_HEATER {\
		SET_BIT(PORTB ,p7);\
		SET_BIT(PORTB ,p1);\
		SET_BIT(PORTE ,p0);\
}

/*  macro OFF_HEATER
 *  Lamp is OFF
 *   Heater is OFF
 *   Motor is OFF
 *    stop time
 *
 */
#define OFF_HEATER {\
        CLEAR_BIT(PORTB ,p7);\
		CLEAR_BIT(PORTB ,p1);\
		CLEAR_BIT(PORTE ,p0);\
		check=1;\
}

#endif /* MICROWAVE_H_ */
