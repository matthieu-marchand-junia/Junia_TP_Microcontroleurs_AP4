#include <xc.h>
#include "pot.h"

#ifndef _POT_C_
#define _POT_C_

void config_pot() {
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA0 = 1;
    ADCON0bits.CHS = 0b00000; 
    ADCON0bits.ADON = 1; 
    ADCON1bits.ADFM = 0; 
}

// Retourne la valeur du potentiomètre
unsigned char read_pot() {
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO){}
    return ADRESH;
}

#endif