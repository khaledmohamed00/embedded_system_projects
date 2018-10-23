#ifndef LCD_H
#define LCD_H

#define LCD_DDR DDRB
#define LCD_DATA PORTB                //LCD data port
#define ctrl PORTC
#define ctrl_DDR DDRC
#define en 2                         // enable signal
#define rw 1                       // read/write signal
#define rs 0                     // register select signal
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_write_string(unsigned char *str);
void LCD_write_int(int number);
void LCD_write_double(double number);
#endif
