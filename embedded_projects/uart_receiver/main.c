#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "uart.h"

int main(void){
DDRC=(1<<DDC0);
/*DDRD|=(1<<DDD0);
DDRC=(1<<DDC0);

int UBRR_value=25;
UBRRH=(unsigned char)(UBRR_value>>8);
UBRRL=(unsigned char)UBRR_value;

UCSRB=(1<<RXEN)|(1<<TXEN);
UCSRC=(1<<USBS)|(3<<UCSZ0);*/
uart_init();

unsigned char receiveData;
while(1){
    
  /*while(!(UCSRA & (1<<RXC)));*/

  receiveData=uart_receive_char();
  if(receiveData==0b11110000)
  {
    PORTC^=(1<<PINC0);
    _delay_ms(200);  
  }


         }




}
