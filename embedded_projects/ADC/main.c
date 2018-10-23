#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include <stdio.h>
#include<uart.h>
#include<debug.h>

FILE usart_str = FDEV_SETUP_STREAM(USARTSendByte, USARTReceiveByte, _FDEV_SETUP_RW);
volatile int flag;
volatile uint16_t analogVal;
int main(void){
ADMUX|=(1<<REFS0);//set reference votage AVCC and A/D ch ADC0
ADCSR |=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADFR)|(1<<ADIE);//prescaler 128 ,enable adc and enable ADC ISR 
sei();
ADCSR|=(1<<ADSC);//start conversion
stdin=stdout = &usart_str;
uart_init();
while(1){
if (flag==1)
{printf("temp%u\n",(uint16_t)(5*100*analogVal)/(1024));
flag=0;
}
}


return 0;
}
ISR(ADC_vect){
flag=1;
analogVal=ADCL|(ADCH<<8);


}

