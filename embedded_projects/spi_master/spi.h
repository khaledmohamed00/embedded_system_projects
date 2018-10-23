#ifndef SPI_H
#define SPI_H

#define ACK 0x7E
void spi_slave_init(void);
void spi_master_init(void);
unsigned char spi_send_receive(unsigned char data);









#endif 
