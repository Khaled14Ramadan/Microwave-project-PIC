/*
 * File:   timer1.c
 * Author: Khaled Ramadan
 */
#include"timer1.h"


void timer1_INT(void)
{
    //Enable TMR1 interrupt
    TMR1IE = 1 ;
    PEIE = 1 ;
    GIE = 1 ;
   
    // clear TMR1 Register , to start counter from 0
    TMR1 = 3036 ;
    
    // select the local clock as TMR1 clock source
    TMR1CS = 0 ;
    
    //set the pre-scaler to 1:4
    T1CKPS0 = 0 ;
    T1CKPS1 = 1 ;
    
    //turn on TMR1 module
    TMR1ON = 1;
}
