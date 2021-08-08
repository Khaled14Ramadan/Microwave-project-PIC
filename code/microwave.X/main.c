/*
 * File:   main.c
 * Author: AL-Esraa
 *
 * 
 */




#include"microwave.h"

uint8 num_sec=0; //the number of second
uint8 num_minuts=0; // the number of minutes
volatile uint8 check=1;
volatile uint8 check_cancel=0;



// External INT enable and configuration function
void INT_IRQ(void)
{
    //RB0 is the input pin to cancel button
    TRISB |=(1<<0);
    GIE = 1 ;
    INTE =1 ;
    INTEDG =1;
}



void main(void) {
    
    uint8 num_sec1=0;
	uint8 num_sec2=0;

	uint8 num_minut1=0;
	uint8 num_minut2=0;
    
    uint8 start =0;/* to change when bush button start */
    uint8 check_lcd=0; /*to print on LCD only one and don't repeat print */
    
    TRISA &= 0x30 ;//to do pin 0,1,2,3 on portA (output)
    PORTA &= 0x30 ;//output for pin 0,1,2,3 =0
    
    TRISC &= 0xF0 ;//to display timer on 7 segment
    PORTC &= 0xF0 ;//start 0
    
    
    /* internal pull ap
	 * RD7 is the input pin to start button
	 * RA4 is the input pin to door sensor
	 * RB6 is the input pin to weight sensor
	 */
	SET_BIT(TRISD , p7);

	SET_BIT(TRISA , p4);

	SET_BIT(TRISB , p6);

	/* output pins
	 * RB7 is the output pin to led
	 * RB3 is the output pin to heater
	 * RB1 and RB2 are the output pin to motor
	 */
	CLEAR_BIT(TRISB , p7);
	CLEAR_BIT(PORTD , p7);

	/* motor */
	CLEAR_BIT(TRISB , p1);
	CLEAR_BIT(PORTB , p1);
	CLEAR_BIT(TRISB , p2);
	CLEAR_BIT(PORTB , p2);

	/* Heater */
	CLEAR_BIT(TRISE , p0);
	CLEAR_BIT(PORTE , p0);


    
    
    /* initialize LCD */
	LCD_init();

	/* to enter the number of timer on keypad */
	LCD_clearScreen();
	LCD_displayString("Enter new time");
    
    while(num_minuts ==0)
	{

		num_minut2 = Key_getPressedKey();
		/* to show num_minut2 on 7_segement */
		PORTA =(PORTA & 0x30) | 0x08;
		PORTC =(PORTC & 0xF0)|(num_minut2 & 0x0F);
		__delay_ms(500);

		num_minut1 = Key_getPressedKey();

		num_minuts=num_minut2 *10 + num_minut1;
	}
    /*
     * enable interrupt on RB0
     *  closed button
     */
    INT_IRQ();
    
    /* work timer */
    timer1_INT();
    
    
    
    for(;;)
    {
       /*
		 * this is macro to timer
		 */
		TIMER(num_sec1 , num_sec2 , num_minut1 , num_minut2);
		/***********************************************************/

		if(check_cancel ==0) /* this not push cancel button */
		{
			/*
			 * RA4 to to check Door sensor
			 * RA5 to check weight sensor
			 */
			if((BIT_IS_CLEAR(PORTB , p6)) && (BIT_IS_CLEAR(PORTA , p4)) )
			{



				check_lcd =0;/*to start LCD from start button */
				while (BIT_IS_SET(PORTD , p7) && start ==0)
				{

					/*
					 * if push cancel button (interrupt 0 )
					 */
					if(check_cancel == 1)
					{
						num_sec1=0;
						num_sec2=0;
						num_minuts=0;
						num_minut1=0;
						num_minut2=0;

						PORTA =(PORTA & 0x30) | 0x01;
						PORTC =(PORTC & 0xF0)|(num_sec1 & 0x0F);

						LCD_clearScreen();
						LCD_displayString("removed time setting");
						__delay_ms(1000);
						LCD_clearScreen();
						LCD_goToRowColumn(1,0);
						LCD_displayString("Enter new time ");

						while(num_minuts ==0)
						{

							num_minut2 = Key_getPressedKey();
							/* to show num_minut2 on 7_segement */
							PORTA =(PORTA & 0xF0) | 0x08;
							PORTC =(PORTC & 0xF0)|(num_minut2 & 0x0F);
							__delay_ms(500);

							num_minut1 = Key_getPressedKey();

							num_minuts=num_minut2 *10 + num_minut1;
						}
						check_cancel=0;
						check_lcd=0;

					}
					/********************************************/
					/*
					 * to display on LCD
					 */
					if(check_lcd == 0)
					{
						LCD_clearScreen();
						LCD_displayString("push start button");
						check_lcd=1;
					}

					TIMER(num_sec1 , num_sec2 , num_minut1 , num_minut2);
				}

				/*
				 * to display on LCD
				 */
				if(check_lcd == 1)
				{
					LCD_clearScreen();
					LCD_displayString("heater is working");
					check_lcd=0;
				}


				/*  macro
				 *  Lamp is ON
				 *   Heater is ON
				 *   Motor is ON
				 *    Display shows remaining time
				 *
				 */
				ON_HEATER
				/****************************************************************/

				start = 1; /* to do not go to pooling to check start button */
				check = 0 ;/* to start decrement time */

				/* to calculate the time */
				if(num_sec > 0)
				{
					if(num_sec == 60)
					{
						num_sec1 = 0;
						num_sec2 = 0;

					}
					else
					{
						num_minut1=(num_minuts % 10);
						num_minut2=(num_minuts /10);

						num_sec1=(num_sec % 10);
						num_sec2=(num_sec /10);
					}

				}
				else if(num_minuts > 0)
				{
					/*when num_sec=0 */
					num_sec=60;


					num_minut1=(num_minuts % 10);
					num_minut2=(num_minuts /10);
					num_minuts--;

				}

				else/* finish time */
				{
					num_sec1=0;

					/*  macro
					 *  Lamp is OFF
					 *   Heater is OFF
					 *   Motor is OFF
					 *    stop time
					 *
					 */

					OFF_HEATER

					/****************************************/

					if(check_lcd == 1)
					{
						LCD_clearScreen();
						LCD_displayString("heating is finish");
						check_lcd=0;
					}

				}
			}

			else /* door is not closed or food is not found */
			{
				/*  macro
				 *  Lamp is OFF
				 *   Heater is OFF
				 *   Motor is OFF
				 *    stop time
				 *
				 */

				OFF_HEATER

				/****************************************/
				if(check_lcd == 0 || start == 1)
				{
					/*to display on LCD
					 * check_lcd==0 if it do not start work
					 * start==0 if it started work
					 */
					LCD_clearScreen();
					LCD_displayString("Door isn't closed");
					LCD_goToRowColumn(1,0);
					LCD_displayString("or not found food");
					check_lcd=1;
					start = 0;
				}
			}

		}


		/* push cancel button */
		else
		{
			if(start==1 )
			{
				/*
				 * heater is working
				 *
				 */

				/*  macro
				 *  Lamp is OFF
				 *   Heater is OFF
				 *   Motor is OFF
				 *    stop time
				 */

				OFF_HEATER
				/****************************************/

				start =0; /* push start button to rework heater */

				check_cancel = 0;
			}
			else
			{
				/*
				 * heater is not working
				 *remove the time
				 */
				num_sec1=0;
				num_sec2=0;
				num_minuts=0;
				num_minut1=0;
				num_minut2=0;


				PORTA =(PORTA & 0x30) | 0x01;
				PORTC =(PORTC & 0xF0)|(num_sec1 & 0x0F);

				LCD_clearScreen();
				LCD_displayString("removed time setting");
				__delay_ms(1000);
				LCD_clearScreen();
				LCD_goToRowColumn(1,0);
				LCD_displayString("Enter new time ");

				while(num_minuts ==0)
				{

					num_minut2 = Key_getPressedKey();
					/* to show num_minut2 on 7_segement */
					PORTA =(PORTA & 0x30) | 0x08;
					PORTC =(PORTC & 0xF0)|(num_minut2 & 0x0F);
					__delay_ms(500);

					num_minut1 = Key_getPressedKey();

					num_minuts=num_minut2 *10 + num_minut1;
				}
				check_cancel=0;
				check_lcd=0;
			}

		}


       
    }
    return;
}



void __interrupt() ISR(void)
{
    
    if(INTF) //External INT on RB0
    {
        check_cancel = 1;
        INTF = 0;   
    }
    
    if(TMR1IF) //timer to count sec
    {
        TMR1 = 3036 ;
        /* if press button stop timer and press again rework timer ( INTERRUPT 0)*/
        if(check %2==0)
        {
        	num_sec--;

        }
        
        TMR1IF = 0;
    }
}


