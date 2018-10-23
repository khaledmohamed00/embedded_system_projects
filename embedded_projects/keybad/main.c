#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "keybad.h"
#include "lcd.h"
#define no_digits 10
int arr_char_to_int(unsigned char * arr){
int index=0;
//int length;
int rank;
while(arr[index]!='\0')
{index++;
}
//length=index;
rank=index;
index=0;
int number;
int sum=0;
while(arr[index]!='\0')
{number=arr[index]-'0';
sum+=number*(pow(10,rank-1));
index++;
rank--;
}
return sum;
}

double calculate(unsigned char * first_arg,unsigned char * sec_arg,unsigned char op){
int first=arr_char_to_int(first_arg);
int second=arr_char_to_int(sec_arg);
switch(op){
case '+':
  return first+second;
case '-':
  return first-second;
case 'x':
  return (1.00*first)*(1.00*second);
case '/':
  return (1.00*first)/(1.00*second);

}
return -5;
}

int main(void){
//DDRC=0xff;
LCD_DDR=0xff;
ctrl_DDR=0x07;
init_LCD();
_delay_ms(50);
//LCD_write_string("hello world");
unsigned char * first_arg=malloc(no_digits*sizeof(unsigned char));   
unsigned char * sec_arg=malloc(no_digits*sizeof(unsigned char));   
int index_first=0;
int index_sec=0;
int flag=0;
unsigned char op;
double result;
while(1){

unsigned char key= pressed_key();
if((key !='+') &&(key!='-')&&(key !='x') &&(key!='=')&&(key !='/') && (key!='c')){
  if(flag==0){
    first_arg[index_first++]=key;
    first_arg[index_first]='\0';
             }
  else{
   sec_arg[index_sec++]=key;
   sec_arg[index_sec]='\0';
      }
         }
else if((key=='+')||(key=='*')||(key=='-')||(key=='x')||(key=='/')){
op=key;
flag=1;
}
else if(key=='=') {
result=calculate(first_arg,sec_arg,op);
//LCD_cmd(0x38);
LCD_write(key);
flag=0;
//LCD_cmd(0x10);
if(result<0){
LCD_write('-');
result*=-1;
}
//result*=-1;
//LCD_write_int(result);
LCD_write_double(result);
_delay_ms(2000);
}
else if(key=='c') {
LCD_cmd(0x01);
index_first=0;
index_sec=0;
}
if(key!='c' && key!='='){
LCD_write(key);
LCD_cmd(0x10);
_delay_ms(2000);
}
}

return 0;
}
