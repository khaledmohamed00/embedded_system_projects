#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include <stdio.h>
#include<uart.h>
#include<debug.h>
#include<stdlib.h>
volatile uint16_t history=0;
volatile uint16_t recent=0; 
volatile uint16_t period=0; 
FILE usart_str = FDEV_SETUP_STREAM(USARTSendByte, USARTReceiveByte, _FDEV_SETUP_RW);
int main(void){

DDRB|=(1<<1)|(1<<3);//set pin 1 and 3 as output

TCCR1A=0x00;//normal mode timer 1
TCCR1B|=(1<<CS10)|(1<<CS11);//prescaler 64 timer 1
TCCR1B|=(1<<ICES1);//Capture on rissing edge timer 1


TCCR2|=(1<<COM21)|(1<<WGM20); //toggle oc2 in compare match OCR2 and phase correct mode  timer 2

TCCR2|=(1<<CS20)|(1<<CS21);//prescaler 64


OCR2=0x5f; //to control duty cycle
//TIMSK|=(1<<TICIE1)|(1<<OCIE1A);
uart_init();//initiate uart
stdin=stdout = &usart_str; // input /out stream
//sei();
uint16_t a,b,c;
uint8_t duty_cycle;
while(1){
TCNT1=0;

while((TIFR &(1<<ICF1))==0);//check input capture flag
a=TCNT1;
TCCR1B&=~(1<<ICES1);//Capture on falling edge
TIFR|=(1<<ICF1);    //reset flag 
while((TIFR &(1<<ICF1))==0);//check input capture flag
b=TCNT1;
TCCR1B|=(1<<ICES1);//Capture on rissing edge
TIFR|=(1<<ICF1);//reset flag 
while((TIFR &(1<<ICF1))==0);//check input capture flag
c=TCNT1;
TIFR|=(1<<ICF1);//reset flag 

if(c>b && b>a){
duty_cycle=(uint8_t)100*(b-a)/(c-a);
printf("duty_cycle=%u %\n",duty_cycle);
printf("freq=%u HZ\n",F_CPU/(64*(c-a)));
}

TCNT1=0;
}

}

//ISR for input capture
ISR(TIMER1_CAPT_vect){
if (history==0)
  history=ICR1;
else{
recent=ICR1;
if(recent-history>0){
period=recent-history;
history=recent;
                    }

     }
}

