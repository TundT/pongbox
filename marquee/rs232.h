#include <stdint.h>
#include <avr/io.h>

#ifndef F_CPU
    #define F_CPU 8000000UL
#endif
#ifndef FOSC
#define FOSC 8000000UL
#endif
#define BAUD 19200
#define MYUBRR FOSC/16/BAUD-1


/* 
 * calculation of ubrr via baudrate
 * UBRR = (f_OSC/(16*BAUD))-1
*/

void init_rs232(uint16_t);
void send_task(void*);
void rs232_putc(char);
void rs232_puts(char *);
void rs232_print_hex(uint8_t);
void rs232_print_hex16(uint16_t);
