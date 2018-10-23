#define F_CPU 1000000
#include<avr/io.h>
#include<util/delay.h>
#include<i2c.h>
#include<EEPROM_24c16b.h>

int main(void){
unsigned char data=0;
DDRD=0xff;
i2c_init_master();


while(1){
EEPROM_write(0xE0,0x00);
_delay_ms(1000);
data=EEPROM_read(0x00);

if(data==0xE0)
PORTD=0xff;


}
return 0;



}



