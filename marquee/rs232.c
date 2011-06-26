#include "rs232.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>



void init_rs232(uint16_t ubrr) {
    /* make sure interrupts are disabled */
    cli();
    /* Set baud rate */
    UBRRH = (unsigned char)(ubrr>>8);
    UBRRL = (unsigned char)ubrr;
    /* Enable receiver and transmitter */
    UCSRB = (1<<RXEN)|(1<<TXEN);
    /* Set frame format: 8data, 1stop bit, no parity*/
    UCSRC = (1<<URSEL)|(0<<USBS)|(3<<UCSZ0)|(0<<UPM0)|(0<<UPM1);

}



/*
 * Print a single character to the serial connection
 */
void rs232_putc(char c) {
    while (!(UCSRA & (1 << UDRE)));

    UDR = (uint8_t) c;
}

/*
 * Print a string (null terminated) to the serial connection
 */
void rs232_puts(char *ptr) {
    uint8_t i=0;

    while(*(ptr+i)) {
        rs232_putc(*(ptr+i));
        i++;
    }
}

/*
 * Print val to the serial connection as a two character hex string
 */
void rs232_print_hex(uint8_t val) {
    uint8_t low = 0x0f & val;
    uint8_t high = (0xf0 & val) >> 4;

    if(high < 10) {
        rs232_putc('0' + high);
    } else {
        rs232_putc('a' + high - 10);
    }

    if(low < 10) {
        rs232_putc('0' + low);
    } else {
        rs232_putc('a' + low - 10);
    }
}

/*
 * Print val to the serial connection as a four character hex string
 */
void rs232_print_hex16(uint16_t val) {
    uint8_t low = 0x00ff & val;
    uint8_t high = val >> 8;

    rs232_print_hex(high);
    rs232_print_hex(low);
}

unsigned char rs232_get( void )
{
    /* Wait for data to be received */
    while ( !(UCSRA & (1<<RXC)) )
        ;
    /* Get and return received data from buffer */
    return UDR;
}

