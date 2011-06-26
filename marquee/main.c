#define F_CPU 8000000UL  // 8 MHz

#include <util/delay.h>

#include <avr/interrupt.h>

#include <avr/io.h>

#include "marquee.h"
#include "display.h"
#include "rs232.h"
#include "adc.h"

uint16_t adc_result = 0;

//#include <util/delay_basic.h>


int main(void)
{
    init_rs232(MYUBRR);
    display_init();
    rs232_puts("# welcome to your marquee terminal \n \r # \n \r #waiting for your text:");
    marquee_setText("hallo welt! das ist ein langer text zum testen des displays!", 0xFF);

    sei();

    _delay_ms(200);

   
	while(1){
        _delay_ms(100);
        marquee_nextStep();
        adc_readChannel(1);
        rs232_puts("test");
    }
	return 0;
}



