/*
 * adc.c
 *
 * Created: 22-04-2017 5:54:02 PM
 *  Author: Admin
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "adc.h"

void adc_init(void)
{
	// Vcc as voltage reference (bits76)
	// right adjustment [ADLAR] (bit5)
	// use ADC0 as input        (bits3210)
	//ADMUX = 0b01100000;
	ADMUX = 0b01000000;
	// enable ADC           (bit7)
	// initialize ADC       (bit6)
	// no autotrigger       (bit5)
	// don't clear int-flag (bit4)
	// no interrupt         (bit3)
	// clock div by 64@8Mhz=125KHz (bit210) ADC should run at 50kHz to 200kHz, 1MHz gives decreased resolution
	ADCSRA = 0b10000011;
	//while(ADC_CSRA & (1<<ADC_SC));	// wait for first conversion to complete
}

// read adc value
unsigned int adc_read(unsigned char _ch)
{
	static uint8_t low, high, tmp;
	// select the corresponding channel 0~7
	// ANDing with '7' will always keep the value
	// of 'ch' between 0 and 7
	// AREF = AVcc
	//ADC_MUX = MUX_REF_VCC | (_ch & 0x07);
	ADMUX = (ADMUX & 0xE0) | (_ch & 0x1F);

	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes '0' again
	// till then, run loop continuously
	while((ADCSRA & (1<<ADSC)) != 0);

	// we have to read ADCL first; doing so locks both ADCL
	// and ADCH until ADCH is read.  reading ADCL second would
	// cause the results of each conversion to be discarded,
	// as ADCL and ADCH would be locked when it completed.
	//low = ADCL;
	//high = ADCH;

	// combine the two bytes
	//return (high << 8) | low;
	//return (ADCH);
	return (ADCW);
}
