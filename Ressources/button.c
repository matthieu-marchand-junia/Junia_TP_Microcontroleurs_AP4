#include <xc.h>
#include "button.h"

#ifndef _BUTTON_C_
#define _BUTTON_C_

void config_button(void) {
    TRISBbits.TRISB0 = 1; // Configuer le port du bouton S1 en lecture
    ANSELBbits.ANSB0 = 0;
}

#endif