#ifndef UART_H
#define UART_H

#define Baud_rate 9600

void uart_init(void);
void uart_send_char(unsigned char c);
unsigned char uart_receive_char(void);

#endif  
