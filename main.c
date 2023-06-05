/*
 * Real time clock.c
 *
 * Created: 6/1/2023 3:50:33 AM
 * Author : kamar salah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
#include "Timer2.h"
#include "LCD driver.h"
#include "seven segment.h"
#include "Keybad driver.h"
#define F_CPU 8000000UL
#include <util/delay.h>

volatile unsigned char counter_seconed=0;
unsigned char counter_minutes=0, counter_hours=0;
unsigned char value, first_digit, seconed_digit;

int main(void)
{
    Keybad_vinit ();
	LCD_vinit ();
	seven_seg_vinti ('B');
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,5);
	
	LCD_vsend_sring ("press 1 to:");
	LCD_vmove_cursor (2,1);
	LCD_vsend_sring ("set clock");
	timer2_overflow_init_interrupt ();
	
    while (1) 
    {
		value=Keybad_u8check_press ();
		if(value!=NOTBRESSED)
		{
			if(value=='1')
			{
				/* setting hours*/
				LCD_vclear_screen ();
				LCD_vsend_sring ("hours=--");
				LCD_vmove_cursor (1,7);
				_delay_ms(500);
				do
				{
					first_digit=Keybad_u8check_press ();
				}while(first_digit==NOTBRESSED);
				LCD_vsend_char (first_digit);
				_delay_ms(300);
				
				do
				{
					seconed_digit=Keybad_u8check_press ();
				}while(seconed_digit==NOTBRESSED);
				LCD_vsend_char (seconed_digit);
				_delay_ms(300);
				counter_hours=(seconed_digit-48)+((first_digit-48)*10) ;
				LCD_vclear_screen ();
				
				/*setting minutes*/
				LCD_vsend_sring ("minutes=--");
				LCD_vmove_cursor (1,9);
				_delay_ms(500);
				do
				{
					first_digit=Keybad_u8check_press ();
				}while(first_digit==NOTBRESSED);
				LCD_vsend_char (first_digit);
				_delay_ms(300);
				
				do
				{
					seconed_digit=Keybad_u8check_press ();
				}while(seconed_digit==NOTBRESSED);
				LCD_vsend_char (seconed_digit);
				_delay_ms(300);
				counter_minutes=(seconed_digit-48)+((first_digit-48)*10) ;
				LCD_vclear_screen ();
				
				/*setting seconds*/
				LCD_vsend_sring ("seconds=--");
				LCD_vmove_cursor (1,9);
				_delay_ms(500);
				do
				{
					first_digit=Keybad_u8check_press ();
				}while(first_digit==NOTBRESSED);
				LCD_vsend_char (first_digit);
				_delay_ms(300);
				
				do
				{
					seconed_digit=Keybad_u8check_press ();
				}while(seconed_digit==NOTBRESSED);
				LCD_vsend_char (seconed_digit);
				_delay_ms(300);
				counter_seconed=(seconed_digit-48)+((first_digit-48)*10) ;
				LCD_vclear_screen ();
				LCD_vsend_sring ("press 1 to:");
	            LCD_vmove_cursor (2,1);
	            LCD_vsend_sring ("set clock");
				
			}
			else
			{
				LCD_vclear_screen ();
				LCD_vsend_sring ("wrong choise");
				_delay_ms(1000);
				LCD_vclear_screen ();
				LCD_vsend_sring ("press 1 to:");
	            LCD_vmove_cursor (2,1);
	            LCD_vsend_sring ("set clock");
			}
				
		}
		
	/* printing seconds */
	SET_BIT(PORTC,1);
	SET_BIT(PORTC,2);
	SET_BIT(PORTC,3);
	SET_BIT(PORTC,4);
	SET_BIT(PORTC,5);
	CLEAR_BIT(PORTC,0);
	seven_seg_vwrite ('B' , counter_seconed %10);
	_delay_ms(5);
	
	SET_BIT(PORTC,0);
	SET_BIT(PORTC,2);
	SET_BIT(PORTC,3);
	SET_BIT(PORTC,4);
	SET_BIT(PORTC,5);
	CLEAR_BIT(PORTC,1);
	seven_seg_vwrite ('B' ,counter_seconed /10);
	_delay_ms(5);
	
	/*printing minutes*/
	SET_BIT(PORTC,0);
	SET_BIT(PORTC,1);
	SET_BIT(PORTC,3);
	SET_BIT(PORTC,4);
	SET_BIT(PORTC,5);
	CLEAR_BIT(PORTC,2);
	seven_seg_vwrite ('B' , counter_minutes %10);
	_delay_ms(5);
	
	SET_BIT(PORTC,0);
	SET_BIT(PORTC,1);
	SET_BIT(PORTC,2);
	SET_BIT(PORTC,4);
	SET_BIT(PORTC,5);
	CLEAR_BIT(PORTC,3);
	seven_seg_vwrite ('B' , counter_seconed /10);
	_delay_ms(5);
	
	/*printing hours*/
	SET_BIT(PORTC,0);
	SET_BIT(PORTC,1);
	SET_BIT(PORTC,2);
	SET_BIT(PORTC,3);
	SET_BIT(PORTC,5);
	CLEAR_BIT(PORTC,4);
	seven_seg_vwrite ('B' , counter_hours %10);
	_delay_ms(5);
	
	SET_BIT(PORTC,0);
	SET_BIT(PORTC,1);
	SET_BIT(PORTC,2);
	SET_BIT(PORTC,3);
	SET_BIT(PORTC,4);
	CLEAR_BIT(PORTC,5);
	seven_seg_vwrite ('B' , counter_hours /10);
	_delay_ms(5);
	
	if(counter_seconed==60)
	{
		counter_seconed=0;
		counter_minutes++;
	}
	
	if(counter_minutes==60)
	{
		counter_minutes=0;
		counter_hours++;
	}
	
	if(counter_hours==24)
	{
		counter_hours=0;
	}
				
    }
}

ISR(TIMER2_OVF_vect)
{
	counter_seconed++;
}

