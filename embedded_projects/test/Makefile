#avr-gcc -g -Os -mmcu=atmega328p -c main.c

#avr-gcc -g -Os -mmcu=atmega328p -c adc.c

#avr-gcc -g -Os -mmcu=atmega328p -c lcdlib.c

#avr-gcc -g -mmcu=atmega328p -Wl,-Map,main.map -o main.elf main.o adc.o lcdlib.o

#avr-objdump -h -S main.elf > main.lst

#avr-objcopy -j .text -j .data -O ihex main.elf main.hex

MCU=atmega328p
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues

main.hex : main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf : main.o adc.o lcdlib.o
	avr-gcc -g -mmcu=atmega328p -Wl,-Map,main.map -o main.elf main.o adc.o lcdlib.o
main.lst : main.elf
	 avr-objdump -h -S main.elf > main.lst
main.o : main.c
	avr-gcc -g -Os -mmcu=atmega328p -c main.c
adc.o : adc.c  	
	avr-gcc -g -Os -mmcu=atmega328p -c adc.c
lcdlib.o : lcdlib.c
	avr-gcc -g -Os -mmcu=atmega328p -c lcdlib.c

#load: main.hex
 #   avrdude -P /dev/ttyUSB0 -p m168 -c stk500v2 -e -U #flash:w:main.hex

	 
