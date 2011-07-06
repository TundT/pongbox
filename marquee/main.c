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

    sei();


    display_setBlendFactor(0);
    _delay_ms(300);

    uint8_t i = 0;
    for(; i<(0xFF-3); i+=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }
    display_setBuffer(BUFFER_B);
    display_clearAll();

    for(; i>4; i-=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }    

    display_setBuffer(BUFFER_A);
    display_clearAll();
    _delay_ms(50);
    marquee_writeText("3", 0xFF, 4);

    for(i = 0; i<(0xFF-3); i+=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }
    for(; i>3; i-=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }    

    display_setBuffer(BUFFER_A);
    display_clearAll();
    _delay_ms(50);
    marquee_writeText("2", 0xFF, 4);

    for(; i<(0xFF-3); i+=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }
    for(; i>3; i-=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }    

    display_setBuffer(BUFFER_A);
    display_clearAll();
    _delay_ms(50);

    marquee_writeText("1", 0xFF, 4);
   
    for(i = 0; i<(0xFF-3); i+=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    }
    for(; i>3; i-=4){
        _delay_ms(7);
        display_setBlendFactor(i);
    } 


    display_setBuffer(BUFFER_A);
    display_clearAll();
    display_setBlendFactor(255);



    marquee_setText("hallo welt! das ist ein langer text zum testen des displays!", 0xFF);

    _delay_ms(100);

   
	while(1){
        _delay_ms(100);
        marquee_nextStep();
        adc_readChannel(1);
        rs232_puts("test");
    }
	return 0;
}



