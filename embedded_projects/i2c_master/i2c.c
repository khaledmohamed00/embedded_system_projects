#define F_CPU 1000000
#include<avr/io.h>
#include<i2c.h>
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)

void i2c_init_master(void){

TWBR=BITRATE(TWSR=0x00);
TWCR|=(1<<TWEN);
//TWSR=0x00 ;
//TWBR=0x47 ;
//TWCR=0x04 ;
}
void i2c_start(void){

TWCR =(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while((TWCR & (1<<TWINT))==0);

}

void i2c_stop(void){
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}

void i2c_write_master_ack(unsigned char data){
TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
while((TWCR & (1<<TWINT))==0);
}


unsigned char i2c_read_master_ack(unsigned char isLast){
if(isLast==0)
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
else
  TWCR=(1<<TWINT)|(1<<TWEN);

while((TWCR & (1<<TWINT))==0);
return (TWDR);

}

void i2c_init_slave(unsigned char slaveAddress){

TWCR=(1<<TWEN);
TWAR=slaveAddress;
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

}

void i2c_send_slave_ack(unsigned char data)
{
TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
while((TWCR & (1<<TWINT))==0);

}

unsigned char i2c_receive_slave_ack(unsigned char isLast){
if(isLast==0)
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
else
  TWCR=(1<<TWINT)|(1<<TWEN);

while((TWCR & (1<<TWINT))==0);
return (TWDR);

}

void i2c_listen_slave(void){

while((TWCR & (1<<TWINT))==0);
}


void i2c_write_master_nack(unsigned char data){
/*TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN);
while((TWCR & (1<<TWINT))==0);*/
TWDR=data;

       TWCR= (1<<TWINT)|(1<<TWEN);

       while (get_bit(TWCR,TWINT)==0)

       {

       }

}


unsigned char i2c_read_master_nack(unsigned char isLast){
if(isLast==0)
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
else
  TWCR=(1<<TWINT)|(1<<TWEN);

while((TWCR & (1<<TWINT))==0);
return (TWDR);

}

void i2c_send_slave_nack(unsigned char data)
{
TWDR=data;
TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
while((TWCR & (1<<TWINT))==0);

}

unsigned char i2c_receive_slave_nack(unsigned char isLast){
if(isLast==0)
  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
else
  TWCR=(1<<TWINT)|(1<<TWEN);

while((TWCR & (1<<TWINT))==0);
return (TWDR);

}

