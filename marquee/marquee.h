#ifndef __MARQUEE_H
#define __MARQUEE_H

    /*******************************\
    *                               *
    *                               *
    *                               *
    *                               *
    \*******************************/

void marquee_setText(char* pText, uint8_t rep);
uint8_t marquee_nextStep();

uint8_t writeletter(char c, int8_t pos);
#endif
