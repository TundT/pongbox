
#include <avr/io.h>

#include "marquee.h"
#include "display.h"
#include "alphabet.h"

char*   marquee_text = 0;
char*   marquee_actText = 0;
int8_t  marquee_pos = 12;
uint8_t marquee_repetition = 0xFF;

void marquee_setText(char* pText, uint8_t rep){
    marquee_pos = 12;
    marquee_text = pText;
    marquee_actText = pText; 
    marquee_repetition = rep;
}

uint8_t marquee_nextStep(){
    uint8_t i   = 0;
    int8_t  pos = marquee_pos;
    char* c     = marquee_actText;
    
    if(marquee_actText[0] != 0){
        
        while(c[i] != 0){
            pos += writeletter(c[i], pos);   // Position des nächsten Zeichens bestimmen
            display_clear(pos++);

            if(pos <-8 ){                   // beim nächsten durchlauf können die ersten zeichen weg gelassen werden
                marquee_pos = pos;
                marquee_actText = &(c[i+1]);
            }else if(pos > 12)              // weitere Zeichen sind noch nicht sichtbar
                break;

            i++;                                 // auf zum nächsten Buchstaben
        }   

        marquee_pos--;

        return 0;
    }

    if(marquee_repetition != 0){
        if(marquee_repetition != 0xFF)
            marquee_repetition--;
        marquee_pos = 12;
        marquee_actText = marquee_text;

        return 0; 
    }

    return 1;
}

uint8_t writeletter(char c, int8_t pos){
    switch(c){
        case '1':
            display_write8(number_1,sizeof(number_1),pos);
            return(sizeof(number_1));
        case '2':
            display_write8(number_2,sizeof(number_2),pos);
            return(sizeof(number_2));
        case '3':
            display_write8(number_3,sizeof(number_3),pos);
            return(sizeof(number_3));

        case 'a':
            display_write8(letter_a,sizeof(letter_a),pos);
            return(sizeof(letter_a));
        case 'b':
            display_write8(letter_b,sizeof(letter_b),pos);
            return(sizeof(letter_b));
        case 'c':
            display_write8(letter_c,sizeof(letter_c),pos);
            return(sizeof(letter_c));
        case 'd':
            display_write8(letter_d,sizeof(letter_d),pos);
            return(sizeof(letter_d));
        case 'e':
            display_write8(letter_e,sizeof(letter_e),pos);
            return(sizeof(letter_e));
        case 'f':
            display_write8(letter_f,sizeof(letter_f),pos);
            return(sizeof(letter_f));
        case 'g':
            display_write8(letter_g,sizeof(letter_g),pos);
            return(sizeof(letter_g));
        case 'h':
            display_write8(letter_h,sizeof(letter_h),pos);
            return(sizeof(letter_h));
        case 'i':
            display_write8(letter_i,sizeof(letter_i),pos);
            return(sizeof(letter_i));
        case 'j':
            display_write8(letter_j,sizeof(letter_j),pos);
            return(sizeof(letter_j));
        case 'k':
            display_write8(letter_k,sizeof(letter_k),pos);
            return(sizeof(letter_k));
        case 'l':
            display_write8(letter_l,sizeof(letter_l),pos);
            return(sizeof(letter_l));
        case 'm':
            display_write8(letter_m,sizeof(letter_m),pos);
            return(sizeof(letter_m));
        case 'n':
            display_write8(letter_n,sizeof(letter_n),pos);
            return(sizeof(letter_n));
        case 'o':
            display_write8(letter_o,sizeof(letter_o),pos);
            return(sizeof(letter_o));
        case 'p':
            display_write8(letter_p,sizeof(letter_p),pos);
            return(sizeof(letter_p));	
        case 'q':
            display_write8(letter_q,sizeof(letter_q),pos);
            return(sizeof(letter_q));	
        case 'r':
            display_write8(letter_r,sizeof(letter_r),pos);
            return(sizeof(letter_r));	
        case 's':
            display_write8(letter_s,sizeof(letter_s),pos);
            return(sizeof(letter_s));
        case 't':
            display_write8(letter_t,sizeof(letter_t),pos);
            return(sizeof(letter_t));
        case 'u':
            display_write8(letter_u,sizeof(letter_u),pos);
            return(sizeof(letter_u));
        case 'v':
            display_write8(letter_v,sizeof(letter_v),pos);
            return(sizeof(letter_v));
        case 'w':
            display_write8(letter_w,sizeof(letter_w),pos);
            return(sizeof(letter_w));
        case 'x':
            display_write8(letter_x,sizeof(letter_x),pos);
            return(sizeof(letter_x));
        case 'y':
            display_write8(letter_y,sizeof(letter_y),pos);
            return(sizeof(letter_y));
        case 'z':
            display_write8(letter_z,sizeof(letter_z),pos);
            return(sizeof(letter_z));
        case '.':
            display_write8(letter_fullstop,sizeof(letter_fullstop),pos);
            return(sizeof(letter_fullstop));
        case '!':
            display_write8(letter_exclamation,sizeof(letter_exclamation),pos);
            return(sizeof(letter_exclamation));
        case '?':
            display_write8(letter_question,sizeof(letter_question),pos);
            return(sizeof(letter_question));

        case ' ':
            display_write8(letter_space,sizeof(letter_space),pos);
            return(sizeof(letter_space));

        default:            
            display_write8(letter_unknown,sizeof(letter_unknown),pos);
            return(sizeof(letter_unknown));
    }
}
