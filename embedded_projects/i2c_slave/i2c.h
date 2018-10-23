#ifndef I2C_H
#define I2C_H
#include<math.h>
#define SCL_CLK 50000 
#define BITRATE(TWSR) ((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR & ((1<<TWPS0)|(1<<TWPS1)))))

void i2c_init_master(void);
void i2c_init_slave(unsigned char slaveAddress);
void i2c_start(void);
void i2c_stop(void);
void i2c_write_master_ack(unsigned char data);
unsigned char i2c_read_master_ack(unsigned char isLast);
void i2c_send_slave_ack(unsigned char data);
unsigned char i2c_receive_slave_ack(unsigned char isLast);
void i2c_write_master_nack(unsigned char data);
unsigned char i2c_read_master_nack(unsigned char isLast);
void i2c_send_slave_nack(unsigned char data);
unsigned char i2c_receive_slave_nack(unsigned char isLast);
void i2c_listen_slave(void);

#endif
