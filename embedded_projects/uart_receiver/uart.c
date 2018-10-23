#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "uart.h"

#define UBBRValue ((F_CPU/Baud_rate)-1)

void uart_init(void){
DDRD|=(1<<DDD1);
DDRD&=~(1<<DDD0);
UBRRH=(unsigned char)(UBBRValue>>8);
UBRRL=(unsigned char)UBBRValue;
UCSRB=(1<<RXEN)|(1<<TXEN);
UCSRC=(1<<USBS)|(3<<UCSZ0);


}

void uart_send_char(unsigned char c){
while(!(UCSRA & (1<<UDRE)));

      UDR=c;

}

unsigned char uart_receive_char(void){
while(!(UCSRA & (1<<RXC)));
return UDR;
}
