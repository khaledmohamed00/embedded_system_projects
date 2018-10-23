/*#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"spi.h"
*/
/*int main (void)
{DDRD=0xff;
    char data=0x00;
    spi_master_init();
  
    while(1)
    {
      
PORTD=spi_send_receive(data++);    

}
}

*/


/*
volatile unsigned char data=0x00;
int main(void){
DDRD=0xff;
DDRB |=(1<<2)|(1<<3)|(1<<5);
DDRB &=~(1<<4);
SPCR |=(1<<MSTR);
SPCR |=(1<<SPR0)|(1<<SPR1);
//SPCR |=(1<SPIE);
SPCR |=(1<<SPE);

//sei();

while(1){
//if ((SPSR & (1<<SPIF)) > 0)
//spi_send_receive(data++);
//SPDR=data++;
//while(!(SPSR & (1<<SPIF)));
//_delay_ms(50);

unsigned char a=spi_send_receive(data++);
}
}*/
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char data;

int main (void)
{
   unsigned char value=0x00;

    DDRB |= (1<<2)|(1<<3)|(1<<5);    // SCK, MOSI and SS as outputs
    DDRB &= ~(1<<4);                 // MISO as input

    SPCR |= (1<<MSTR);               // Set as Master
    SPCR |= (1<<SPR0)|(1<<SPR1);     // divided clock by 128
    SPCR |= (1<<SPIE);               // Enable SPI Interrupt    
    SPCR |= (1<<SPE);                // Enable SPI


   // sei();    

    while(1)
    {
       // if ((SPSR & (1<<SPIF)) )  // checks to see if the SPI bit is clear
            SPDR=value++;              // send the data
            while(!(SPSR & (1<<SPIF)) );
        // if you use multiple slaves, switch slave here.
    }
}

/*
ISR (SPI_STC_vect)
{
    SPDR = data;
}*/
