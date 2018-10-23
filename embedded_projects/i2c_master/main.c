#define F_CPU 1000000
#include<avr/io.h>
#include<util/delay.h>
#include<i2c.h>


int main(void){

i2c_init_master();

i2c_start();
i2c_write_master_ack(0b11010000);
i2c_write_master_ack(0b11110000);
i2c_stop();


while(1){

}
return 0;



}



