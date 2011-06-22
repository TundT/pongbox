AVRDUDE_PORT = /dev/ttyUSB0
#AVRDUDE_PORT = /dev/ttyACM0

MCU = atmega8
CFLAGS = -O2

all: main.o
	avr-objcopy -j .text -j .data -O ihex main.o main.hex

install:
	avrdude -e -p $(MCU) -c stk500v2 -P $(AVRDUDE_PORT) -U flash:w:main.hex

main.o: main.c display.c display.h marquee.c marquee.h alphabet.h
	avr-gcc -mmcu=$(MCU) $(CFLAGS) main.c display.c marquee.c -o main.o

clean:
	@echo cleaning
	rm -f main.o main.hex

