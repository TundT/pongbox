#define F_CPU 8000000UL  // 8 MHz

#include <util/delay.h>

#include <avr/interrupt.h>

#include <avr/io.h>

#include "alphabet.h"
//#include <util/delay_basic.h>

uint8_t rowNr = 0;

inline void writerow(uint16_t row);
//void startrow();
//void nextrow();
void writetext(char* c,uint8_t pos);
uint8_t writeletter(char c, uint8_t pos);
void copy2image(uint8_t* s, uint8_t len, uint8_t pos);


ISR( TIMER2_OVF_vect ){
    cli();
    writerow(image[rowNr]); 

    if(rowNr >= 11){
        PORTB = PORTB & 0b11101111; // set Data 0
        rowNr=0;
    }else{
        if (rowNr == 0)
            PORTB = PORTB | 0b00010000; // set Data 1 -> für die nächsten schritte 
        rowNr++;
    }
    sei();
}


int main(void)
{
    DDRC = 0x0F;
    DDRD = 0xF0;
    DDRB = 0x03;

    DDRB |= 0x04 | 0x08 | 0x10;
    PORTB = 0x0;
    
    TIMSK = 0x0;
    TCCR1A = 0x0;
    TCCR1B = 0x0 | 0b101;   // 1024 als teiler

    TCNT0 = 0x0;

   
    TCCR2  = (0<<CS22) | (1<<CS21) | (1<<CS20);      //32 als prescaler
    //TCCR2  = (0<<CS22) | (1<<CS21) | (0<<CS20);      //8 als prescaler
    TCCR2 |= (1<<WGM20) | (1<<WGM21);                // WGM macht Fast-PWM
    TCCR2 |= (1<<COM21);                             // Clear OC2 on Compare Match
    //TCCR2 |= (1<<COM21) | (1<<COM20);                // Set OC2 on Compare Match

    //IRC2 = 0x6FFF;          // maximalwert
    //OCR2 = 0x02;         // wert bei dem von 0 auf 1 gewechselt wird....
    OCR2 = 0x7F;         // wert bei dem von 1 auf 0 gewechselt wird....

    TIMSK |= (1<<TOIE2);       // enable timer2 overflow interrupt

    PORTB = PORTB | 0b00000100;  // strobe auf high

    sei();

    //writerow(0b0011001100);


    int8_t i = 12;
    _delay_ms(200);


	while(1){
        i--;
        _delay_ms(100);
        writetext("hallo welt!",i);

        if(i < -127)
            i = 12;
    }
	return 0;
}

void writetext(char* c ,uint8_t pos){
    uint8_t i = 0;

    while(c[i] != 0){
        pos += 1 + writeletter(c[i], pos);   // Position des nächsten Zeichens bestimmen
        i++;                                 // auf zum nächsten Buchstaben
    }    
}

uint8_t writeletter(char c, uint8_t pos){
    switch(c){
        case 'a':
            copy2image(letter_a,sizeof(letter_a),pos);
            return(sizeof(letter_a));
        case 'b':
            copy2image(letter_b,sizeof(letter_b),pos);
            return(sizeof(letter_b));
        case 'c':
            copy2image(letter_c,sizeof(letter_c),pos);
            return(sizeof(letter_c));
        case 'd':
            copy2image(letter_d,sizeof(letter_d),pos);
            return(sizeof(letter_d));
        case 'e':
            copy2image(letter_e,sizeof(letter_e),pos);
            return(sizeof(letter_e));
        case 'f':
            copy2image(letter_f,sizeof(letter_f),pos);
            return(sizeof(letter_f));
        case 'g':
            copy2image(letter_g,sizeof(letter_g),pos);
            return(sizeof(letter_g));
        case 'h':
            copy2image(letter_h,sizeof(letter_h),pos);
            return(sizeof(letter_h));
        case 'i':
            copy2image(letter_i,sizeof(letter_i),pos);
            return(sizeof(letter_i));
        case 'j':
            copy2image(letter_j,sizeof(letter_j),pos);
            return(sizeof(letter_j));
        case 'k':
            copy2image(letter_k,sizeof(letter_k),pos);
            return(sizeof(letter_k));
        case 'l':
            copy2image(letter_l,sizeof(letter_l),pos);
            return(sizeof(letter_l));
        case 'm':
            copy2image(letter_m,sizeof(letter_m),pos);
            return(sizeof(letter_m));
        case 'n':
            copy2image(letter_n,sizeof(letter_n),pos);
            return(sizeof(letter_n));
        case 'o':
            copy2image(letter_o,sizeof(letter_o),pos);
            return(sizeof(letter_o));
        case 'p':
            copy2image(letter_p,sizeof(letter_p),pos);
            return(sizeof(letter_p));	
        case 'q':
            copy2image(letter_q,sizeof(letter_q),pos);
            return(sizeof(letter_q));	
        case 'r':
            copy2image(letter_r,sizeof(letter_r),pos);
            return(sizeof(letter_r));	
        case 's':
            copy2image(letter_s,sizeof(letter_s),pos);
            return(sizeof(letter_s));
        case 't':
            copy2image(letter_t,sizeof(letter_t),pos);
            return(sizeof(letter_t));
        case 'u':
            copy2image(letter_u,sizeof(letter_u),pos);
            return(sizeof(letter_u));
        case 'v':
            copy2image(letter_v,sizeof(letter_v),pos);
            return(sizeof(letter_v));
        case 'w':
            copy2image(letter_w,sizeof(letter_w),pos);
            return(sizeof(letter_w));
        case 'x':
            copy2image(letter_x,sizeof(letter_x),pos);
            return(sizeof(letter_x));
        case 'y':
            copy2image(letter_y,sizeof(letter_y),pos);
            return(sizeof(letter_y));
        case 'z':
            copy2image(letter_z,sizeof(letter_z),pos);
            return(sizeof(letter_z));
        case '.':
            copy2image(letter_fullstop,sizeof(letter_fullstop),pos);
            return(sizeof(letter_fullstop));
        case '!':
            copy2image(letter_exclamation,sizeof(letter_exclamation),pos);
            return(sizeof(letter_exclamation));
        case '?':
            copy2image(letter_question,sizeof(letter_question),pos);
            return(sizeof(letter_question));

        case ' ':
            return(0);

        default:            
            copy2image(letter_x,5,0*pos);
            return(5);
    }
}

void copy2image(uint8_t* s ,uint8_t len, uint8_t pos){

    uint8_t tmp = 0;
    uint8_t i = 0;

    //pos += 12;       // Zentrierung auf dem Display    
    

    for(; i< len; i++){
        tmp = i + pos;
        if(tmp > 11)
            continue;
        image[tmp] = (uint16_t)(s[i]) << 1;
    }
    tmp = pos +len;
    if(tmp < 12)
        image[tmp] = 0;
}

/*void nextrow(){
    rowNr++;

    if(rowNr >=12){
        PORTB = PORTB | 0b00000100;  // strobe auf high
        PORTB = PORTB & 0b11101111; // set Data 0
        rowNr = 0;
    }
    _delay_ms(0.6);
    PORTB = PORTB & 0b11110111; // fallenden Clock flanke

    PORTB = PORTB | 0b00001000; // steigende Clock flanke
    PORTB = PORTB | 0b00010000; // set Data 1 -> für die nächsten schritte 

    
}*/

inline void writerow(uint16_t row){
     PORTC = (PORTC & 0xF0) | (row & 0x0F);
     PORTD = (PORTC & 0x0F) | (row & 0xF0);
     PORTB = (PORTB & 0xFC) | (row>>8 & 0x03);
} 
