#include "adc.h"

uint16_t adc_readChannel(uint8_t mux) {
    uint16_t result;
 
    ADMUX = mux; // choose channel
    ADMUX |= (1<<REFS1) | (1<<REFS0); // use internal reference
 
    ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); // set prescaler to 8 and activate adc 
 
    ADCSRA |= (1<<ADSC); // do dummy adc
    while ( ADCSRA & (1<<ADSC) ) {
         ;         // wait for finish
    }
    result = ADCW; // ADCW must be read in order to allow new measurement
 
    result = 0;
    ADCSRA |= (1<<ADSC); // single conversion
        while ( ADCSRA & (1<<ADSC) ) {
            ;     // wait for finish
        }
        result = ADCW;	// save result

    //ADCSRA &= ~(1<<ADEN);  // deactivate adc
 
    return result;
}
