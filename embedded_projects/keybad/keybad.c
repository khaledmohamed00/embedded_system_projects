#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include "keybad.h"


unsigned char pressed_key(void){

KEY_DDR=0x0f;

KEY_PRT=0xf0;
unsigned char key;
while(KEY_PIN==0xf0);
if(KEY_PIN!=0xf0){
_delay_ms(50);
}
if(KEY_PIN !=0xf0){

//_delay_ms(50);

unsigned char input=KEY_PIN;
input=input & 0xf0;
int row=-1;
int col=-1;
if((input & (1<<4))==0)
  row=0;
else if((input &(1<<5))==0)
  row=1;
else if((input &(1<<6))==0)
  row=2;
else if((input &(1<<7))==0)
 row=3;
if(row!=-1)
 PORTC=0xff;

KEY_DDR=0xf0;
KEY_PRT=0x0f;

input=KEY_PIN;
input=input & 0x0f;
if((input & (1<<0))==0)
  col=0;
else if((input & (1<<1))==0)
  col=1;
else if((input &(1<<2))==0)
  col=2;
else if((input &(1<<3))==0)
 col=3;


if(row==0 && col==0)
 key='7';
else if(row==0 && col==1)
key='8';
else if(row==0 && col==2)
key='9';
else if(row==0 && col==3)
key='/';
else if(row==1 && col==0)
key='4';
else if(row==1 && col==1)
key='5';
else if(row==1 && col==2)
key='6';
else if(row==1 && col==3)
key='x';
else if(row==2 && col==0)
key='1';
else if(row==2 && col==1)
key='2';
else if(row==2 && col==2)
key='3';
else if(row==2 && col==3)
key='-';
else if(row==3 && col==0)
key='c';
else if(row==3 && col==1)
key='0';
else if(row==3 && col==2)
key='=';
else if(row==3 && col==3)
key='+';



}



return key;


}

