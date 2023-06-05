/*
 * Timer2.c
 *
 * Created: 6/1/2023 3:45:22 AM
 *  Author: kamar salah
 */ 
#include "macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
 
void timer2_overflow_init_interrupt (void)
{
	/*select timer clock  from external clock */
	SET_BIT(ASSR,AS2);                                       // using external clock
	
	/*select timer prescaler             >>prescaler=128*/
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);                                   
	
	/*enable interrupt             >> ISR generate every 1 sec*/
	sei();
	SET_BIT(TIMSK,TOIE2);
}