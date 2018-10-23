#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <stdlib.h>
#include <math.h>  

#include<lcd.h>

void init_LCD(void)
{
LCD_cmd(0x38);                            // initialization of 16X2 LCD in 8bit mode
_delay_ms(1);
LCD_cmd(0x01);                                 // clear LCD
_delay_ms(1);
LCD_cmd(0x0E);                        // cursor ON
_delay_ms(1);
LCD_cmd(0x80);                     // —8 go to first line and –0 is for 0th position
_delay_ms(1);
return;
}

void LCD_cmd(unsigned char cmd)
{
LCD_DATA=cmd;
ctrl =(0<<rs)|(0<<rw)|(1<<en);
_delay_ms(1);
ctrl =(0<<rs)|(0<<rw)|(0<<en);
_delay_ms(50);
return;
}

void LCD_write(unsigned char data)
{
LCD_DATA= data;
ctrl = (1<<rs)|(0<<rw)|(1<<en);
_delay_ms(1);
ctrl = (1<<rs)|(0<<rw)|(0<<en);
_delay_ms(50);

return ;
}

void LCD_write_string(unsigned char *str)             //store address value of the string in pointer *str
{
int i=0;
while(str[i]!='\0')                               // loop will go on till the NULL character in the string
{
LCD_write(str[i]);                            // sending data on LCD byte by byte
i++;
}
return;
}

void LCD_write_int(int number){

int num=number;
int digits=0;
int index;
while(num>0){
digits++;
num/=10;
}
index=digits-1;
unsigned char * arr=malloc((digits+1)* sizeof(unsigned char));
while(index>=0){
int rem=number%10;
number=number/10;
arr[index--]=rem+'0';
}
arr[digits]='\0';
LCD_write_string(arr);

}

void LCD_write_double(double number){

int num=(int)number;

LCD_write_int(num);
LCD_write('.');
int factor=(int)(fmod( number, 1.0 )*100);
LCD_write_int(factor);

}
