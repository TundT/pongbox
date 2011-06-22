AVRDUDE_PORT = /dev/ttyUSB0
#AVRDUDE_PORT = /dev/ttyACM0

all:
	avr-gcc -mmcu=atmega8 -O2 main.c -o main.o
	avr-objcopy -j .text -j .data -O ihex main.o main.hex

install:
	avrdude -e -p atmega8 -c stk500v2 -P $(AVRDUDE_PORT) -U flash:w:main.hex

clean:
	@echo cleaning
	rm -f main.o main.hex

