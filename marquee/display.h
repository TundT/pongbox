#ifndef __DISPLAY_H
#define __DISPLAY_H

    /************************************************************
    *
    *
    *
    *
    *    Ports:
    *             7      0
    *       PORTB ---ooooo
    *       PORTC ----oooo
    *       PORTD oooo----
    *
    *
    *    Timers: 
    *       TIMER2 -> PWM
    *
    *    Interrupts:
    *       TIMER2_OVF_vect
    *
    ************************************************************/

#define BUFFER_A 0x01
#define BUFFER_B 0x02

void display_init(void);

void display_setBuffer(uint8_t bufferId);

void display_setBlendFactor(uint8_t bFactor);
// 255 -> only BufferA is Visible
//   0 -> only BufferB is Visible


void display_clear(uint8_t column);
void display_clearAll(void);

void display_write8(uint8_t* pImg, uint8_t len, int8_t xPos);
void display_write8p(uint8_t* pImg, uint8_t len, int8_t xPos, int8_t yPos);

void display_write16(uint16_t* pImg, uint8_t len, int8_t xPos);
void display_write16p(uint16_t* pImg, uint8_t len, int8_t xPos, int8_t yPos);

#endif
