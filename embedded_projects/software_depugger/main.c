#include <avr/io.h>
#include <stdio.h>
#include<uart.h>
#include<debug.h>
FILE usart_str = FDEV_SETUP_STREAM(USARTSendByte, USARTReceiveByte, _FDEV_SETUP_RW);
int main(void)
{DDRC=0xff;
PORTC=0xff;
uint8_t pinc=PINC;
  uart_init();
  stdin=stdout = &usart_str;
  printf("PORTC=%u\n",pinc);
  while(1){

   scanf("%c",&pinc);
   PORTC=pinc;
   pinc=PINC;
   printf("PORTC=%u\n",pinc);
}
  return 0;
}
