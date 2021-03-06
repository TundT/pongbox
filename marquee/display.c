

#include <avr/interrupt.h>
#include <avr/io.h>

#include "display.h"

uint8_t columnNr = 0;
uint8_t blendFactor = 0xFF;

uint16_t bufferA[12] = {0b0000000000,      // column 0
                        0b0001111100,
                        0b0010000010,
                        0b0100011001,
                        0b1001011001,
                        0b1010000001,
                        0b1010000001,
                        0b1001011001,
                        0b0100011001,
                        0b0010000010,
                        0b0001111100,
                        0b0000000000};      // column 11;

uint16_t bufferB[12] = {0b1000000001,      // column 0
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b0000000000,
                        0b1000000001};      // column 11;

uint16_t* buffer = bufferA;


inline void writecolumn(uint16_t column){
     PORTC = (PORTC & 0xF0) | (column & 0x0F);
     PORTD = (PORTC & 0x0F) | (column & 0xF0);
     PORTB = (PORTB & 0xFC) | (column>>8 & 0x03);
} 

ISR( TIMER2_OVF_vect ){
    cli();
    if(blendFactor != 0)
        writecolumn(bufferA[columnNr]); 
    else
        writecolumn(0x0000);

    
    sei();
}

ISR( TIMER2_COMP_vect ){
    cli();
    if(blendFactor != 0xFF)
        writecolumn(bufferB[columnNr]);
    else
        writecolumn(0x0000); 

    if(columnNr >= 11){
        PORTB = PORTB & 0b11101111; // set Data 0
        columnNr=0;
    }else{
        if (columnNr == 0)
            PORTB = PORTB | 0b00010000; // set Data 1 -> für die nächsten schritte 
        columnNr++;
    }

    sei();
}


void display_init(void){

    DDRC  |= 0x0F;           // OR is OK ?????
    DDRD  |= 0xF0;
    DDRB  |= 0x03;

    DDRB  |= 0x04 | 0x08 | 0x10;
    PORTB &= 0xE0;
    
//    TIMSK = 0x0;    // oder so lassen?

    TCNT0 = 0x0;
   
    TCCR2  = (0<<CS22) | (1<<CS21) | (1<<CS20);      //32 als prescaler
    //TCCR2  = (0<<CS22) | (1<<CS21) | (0<<CS20);      //8 als prescaler
    TCCR2 |= (1<<WGM20) | (1<<WGM21);                // WGM macht Fast-PWM
    TCCR2 |= (1<<COM21);                             // Clear OC2 on Compare Match
    //TCCR2 |= (1<<COM21) | (1<<COM20);                // Set OC2 on Compare Match

    OCR2 = 0x7F;            // wert bei dem von 1 auf 0 gewechselt wird....

    TIMSK |= 1<<TOIE2;      // enable Timer/Counter2 Overflow Interrupt
    TIMSK |= 1<<OCIE2;      // enable Output Compare Match Interrupt

    PORTB = PORTB | 0b00000100;  // strobe auf high
}

void display_setBuffer(uint8_t bufferId){

    if(bufferId == BUFFER_A)
        buffer = bufferA;
    else if(bufferId == BUFFER_B)
        buffer = bufferB;
}

void display_setBlendFactor(uint8_t bFactor){
// 255 -> only BufferA is Visible
//   0 -> only BufferB is Visible

    blendFactor = bFactor;

    if(bFactor <= 0x01)
        OCR2 = 0x02;
    else if(bFactor > 0xFD)
        OCR2 = 0xFD;
    else
        OCR2 = bFactor;

}

void display_clear(uint8_t column){
    if(column < 12)
        buffer[column] = 0;
}

void display_clearAll(void){
    uint8_t i = 0;

    for(; i< 12; i++)
        buffer[i] = 0;
}

void display_write8(uint8_t* pImg, uint8_t len, int8_t xPos){

    uint8_t pos = 0;
    uint8_t i = 0;

    for(; i< len; i++){
        pos = i + xPos;
        if(pos <= 11)
            buffer[pos] = (uint16_t)(pImg[i]) << 1;
    }
}

void display_write8p(uint8_t* pImg, uint8_t len, int8_t xPos, int8_t yPos){

    uint8_t pos = 0;
    uint8_t i = 0;

    for(; i< len; i++){
        pos = i + xPos;
        if(pos <= 11)
            buffer[pos] = (uint16_t)(pImg[i]) << yPos;
    }
}

void display_write16(uint16_t* pImg, uint8_t len, int8_t xPos){

    uint8_t pos = 0;
    uint8_t i = 0;

    for(; i< len; i++){
        pos = i + xPos;
        if(pos <= 11)
            buffer[pos] = pImg[i];
    }
}

void display_write16p(uint16_t* pImg, uint8_t len, int8_t xPos, int8_t yPos){

    uint8_t pos = 0;
    uint8_t i = 0;

    if(len < 12){
        for(; i< len; i++){     // position in image
            pos = i + xPos;     // position in buffer
            if(pos <= 11)
                buffer[pos] = pImg[i] << yPos;
        }
    }else{
        for(; i< 12 ;i++){       // position in buffer
            pos = i - xPos;     // position in image
            if(pos < len)
                buffer[i] = pImg[pos] << yPos;
        }
    }
}
