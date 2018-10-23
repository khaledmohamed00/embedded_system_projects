#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "uart.h"

int main(void){
DDRB&=~(1<<DDB0);
PORTB|=(1<<PORTB0);
/*DDRD|=(1<<DDD1);
DDRD&=~(1<<DDD0);

DDRB&=~(1<<DDB0);
PORTB|=(1<<PORTB0);
 
int UBBRValue=25;
UBRRH=(unsigned char)(UBBRValue>>8);
UBRRL=(unsigned char)UBBRValue;

UCSRB=(1<<RXEN)|(1<<TXEN);

UCSRC=(1<<USBS)|(3<<UCSZ0);*/
uart_init();

while(1){

if((PINB&(1<<0))==0)
   {
    /* while(!(UCSRA & (1<<UDRE)));

      UDR=0b11110000;*/
     unsigned char c= 0xff;
     uart_send_char(c);
     
   } 

    _delay_ms(200);
        }


}
