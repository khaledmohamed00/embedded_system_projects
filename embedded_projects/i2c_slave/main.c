#include<avr/io.h>
#include<i2c.h>

int main(void){
DDRD=0xff;

i2c_init_slave(0b11010000);
i2c_listen_slave();
PORTD=i2c_receive_slave_ack(1);
while(1){}
return 0;

}

