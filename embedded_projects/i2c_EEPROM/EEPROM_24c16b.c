#define F_CPU 1000000
#include<avr/io.h>
#include<util/delay.h>
#include<i2c.h>
#include<EEPROM_24c16b.h>
unsigned char EEPROM_read(unsigned char address){

i2c_start();
i2c_write_master_nack(0xA0);
i2c_write_master_nack(address);
i2c_start();
i2c_write_master_nack(0xA1);
unsigned char data=i2c_read_master_nack(1);
//data=i2c_read_master_nack(1);
i2c_stop();

return data;
}

void EEPROM_write(unsigned char data,unsigned char address){
i2c_start();

i2c_write_master_nack(0xA0);
i2c_write_master_nack(address);
i2c_write_master_nack(data);


i2c_stop();


}


