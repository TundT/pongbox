#define F_CPU 8000000UL  // 8 MHz

#include <util/delay.h>

#include <avr/interrupt.h>

#include <avr/io.h>

#include "marquee.h"
#include "display.h"

//#include <util/delay_basic.h>


int main(void)
{
    display_init();
    marquee_setText("hallo welt! \"bei dieser nachricht handelt es sich um eine etwas längere nachricht. dennoch sollte die ausgabe erfolgreich sein\".", 0xFF);

    sei();

    _delay_ms(200);

   
	while(1){
        _delay_ms(100);
        marquee_nextStep();
    }
	return 0;
}



