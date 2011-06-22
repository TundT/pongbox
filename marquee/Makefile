all:
	avr-gcc -mmcu=atmega8 -O2 main.c -o main.o
	avr-objcopy -j .text -j .data -O ihex main.o main.hex

install:
	avrdude -e -p atmega8 -c stk500v2 -P /dev/ttyACM0 -U flash:w:main.hex

clean:
	@echo cleaning
	rm -f main.o main.hex

