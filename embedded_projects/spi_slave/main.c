#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
//#include"spi.h"

/*
int main (void)
{DDRD=0xff;
    char data;
  spi_slave_init();
  
    while(1)
    {
       
     PORTD =spi_send_receive(ACK);
   
 }
}
*/

volatile unsigned char data;
int main (void)
{DDRD=0xff;
    DDRB &= ~((1<<2)|(1<<3)|(1<<5));   // SCK, MOSI and SS as inputs
    DDRB |= (1<<4);                    // MISO as output

    SPCR &= ~(1<<MSTR);                // Set as slave 
    SPCR |= (1<<SPR0)|(1<<SPR1);       // divide clock by 128
    SPCR |=(1<<SPIE);
    SPCR |= (1<<SPE);                   // Enable SPI

    sei();

    while(1)
    {

       // ;
    }
}


ISR (SPI_STC_vect)
{
  //uint8_t y = SPI_SlaveReceive();
  PORTD = SPDR;

}


/*#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile data;

int main (void)
{DDRD=0xff;
    DDRB &= ~((1<<2)|(1<<3)|(1<<5));   // SCK, MOSI and SS as inputs
    DDRB |= (1<<4);                    // MISO as output

    SPCR &= ~(1<<MSTR);                // Set as slave 
    SPCR |= (1<<SPR0)|(1<<SPR1);       // divide clock by 128
    SPCR |= (1<<SPIE);                 // Enable SPI Interrupt
    SPCR |= (1<<SPE);                  // Enable SPI

    sei();

    while(1)
    {
       // ;
    }
}

ISR (SPI_STC_vect)
{PORTD=0x0f;
    data = SPDR;
    // do something with the received data
}*/
