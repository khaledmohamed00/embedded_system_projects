#include <avr/io.h>
#include <stdio.h>
#include<debug.h>
int USARTSendByte(char u8Data, FILE *stream)
{
   if(u8Data == '\n')
   {
      USARTSendByte('\r', 0);
   }
//wait while previous byte is completed
while(!(UCSRA&(1<<UDRE))){};
// Transmit data
UDR = u8Data;
return 0;
}

int USARTReceiveByte(FILE *stream)
{
uint8_t u8Data;
// Wait for byte to be received
while(!(UCSRA&(1<<RXC))){};
u8Data=UDR;
//echo input data
USARTSendByte(u8Data,stream);
// Return received data
return u8Data;
}
