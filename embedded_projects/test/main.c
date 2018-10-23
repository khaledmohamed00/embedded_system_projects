/*
 * GccApplication7.c
 *
 * Created: 22-04-2017 5:53:14 PM
 * Author : Admin
 */ 
#define F_CPU 1000000ul
//#define F_CPU 11059200
#include <avr/io.h>
#include "adc.h"
#include "lcdlib.h"
#include <util/delay.h>
#include <avr/interrupt.h>
static volatile int SEC =0;
static volatile int MIN =0;
static volatile int HOU =0;
#define START_TIMER1 TCCR1B |= (1<<CS0)|(1<<CS2)
#define STOP_TIMER1  TCCR1B &= 0B11111000
int main(void)
{//int SEC =0;
	/*int value;
	LCD_Init();
	adc_init();
  
   int history =0;
    while (1) 
    {
//LCD_Init();
	//_LCD_CLR();
	//_delay_ms(100);
		//lcd_write_int(0);
		//lcd_write_string("Temp= ")	;
		//adc_init(); 
		//lcd_write_int((adc_read(0x0)/2)-1);
		//value = ((adc_read(0)*500.0)/1024.0);
		
		value = ((adc_read(0)*4.8828125)/10);
		if(value!=history)
		{ history=value;
		LCD_CmdWrite(0x0E);	      // Display ON cuRSor ON
		LCD_CmdWrite(0x01);	      // Clear the LCD
		LCD_CmdWrite(0x80);
		lcd_write_string("Temp= ")	;
		//lcd_write_int(value);
		LCD_Integer(value);
		//LCD_DataWrite(value);
		lcd_write_string(" c ");
	//LCD_CmdWrite(0x01);
		}
	}*/
DDRD&=~(1<<DDD2);
PORTD|=(1<<PORTD2);
EICRA|=(1<<ISC00);
EIMSK|=(1<<INT0);	
	sei();
	DDRB=0xf0;
	PORTB=0x0f;
LCD_Init();
TCCR1B |=(1<<CS12)|(1<<CS10)|(1<<WGM12);// setting prescale and CTC mode

//OCR1A=10800;//setting compare value equal to counter clock frequency to get an interrupt every second
OCR1A=0x3d0;
//OCR1A=0xff;

//sei();// enabling global interrupts
//int val=TCNT0_1;
TIMSK1 |=(1<<OCIE1A);//compare match interrupt enable
while(1)
{ if ((PINB & (1<<PINB0))==0)
	{_delay_ms(100);
		if ((PINB & (1<<PINB0))==0)
		{
			
		
		MIN=(MIN+1)%60;
		}
	}
	if ((PINB & (1<<PINB1))==0)
	{_delay_ms(100);
		if ((PINB & (1<<PINB1))==0)
		{
			
			
		HOU=(HOU+1)%24;
	}
	}
	if ((PINB & (1<<PINB2))==0)
	{ if(MIN>0)
		{_delay_ms(100);
			if ((PINB & (1<<PINB2))==0)
			
			{
				
				
		MIN=(MIN-1)%60;
			}
	}
	}
	if ((PINB & (1<<PINB3))==0)
	{ if(HOU>0)
		{_delay_ms(100);
			if ((PINB & (1<<PINB3))==0)
			{
				
				
		HOU=(HOU-1)%24;
			}
		}
	}
	//LCD_Init();
	 //LCD_CmdWrite(0x28);
	 LCD_CmdWrite(0x0E);	      // Display ON cuRSor ON
	 LCD_CmdWrite(0x01);	      // Clear the LCD
	 LCD_CmdWrite(0x80);
	//LCD_CmdWrite(0x1C);
	//LCD_CmdWrite(0x08);
	
	LCD_Integer( HOU);
	lcd_write_string(" : ")	;
	//lcd_write_int(SEC);
 //LCD_CmdWrite(0x80 + 3);	
//lcd_write_int(SEC);
LCD_Integer(MIN);
// LCD_CmdWrite(0x80 + 3);
  lcd_write_string(" : ")	;

LCD_Integer( SEC);
_delay_ms(15);
}
}

ISR(TIMER1_COMPA_vect) //loop to be executed on counter compare match

{

	if (SEC<60)

	{

		SEC++;

	}
 if (SEC==60)
 {
	 if (MIN<60)
	 {
		 MIN++;
	 }
	 SEC=0;
 }
 if (MIN==60)
 {
	 if (HOU<24)
	 {
		 HOU++;
	 }
	 MIN=0;
 }
 if (HOU==24)
 {
	 HOU=0;
 }
}
ISR(INT0_vect)
{
	
	int value;
	LCD_Init();
	adc_init();
  
   int history =0;
   // while (1) 
    //{
//LCD_Init();
	//_LCD_CLR();
	//_delay_ms(100);
		//lcd_write_int(0);
		//lcd_write_string("Temp= ")	;
		//adc_init(); 
		//lcd_write_int((adc_read(0x0)/2)-1);
		//value = ((adc_read(0)*500.0)/1024.0);
		
		value = ((adc_read(0)*4.8828125)/10);
		if(value!=history)
		{ history=value;
		LCD_CmdWrite(0x0E);	      // Display ON cuRSor ON
		LCD_CmdWrite(0x01);	      // Clear the LCD
		LCD_CmdWrite(0x80);
		lcd_write_string("Temp= ")	;
		//lcd_write_int(value);
		LCD_Integer(value);
		//LCD_DataWrite(value);
		lcd_write_string(" c ");
	//LCD_CmdWrite(0x01);
		_delay_ms(1000);
		}
	//}
	
	
	
}