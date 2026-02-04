#include <xc.h>
#include "interrupt.h"
#ifndef _INTERRUPT_C_
#define	_INTERRUPT_C_

void config_interrupt(void) {
    INTCONbits.GIE = 1; // Activer les interruptions globales
    INTCONbits.PEIE = 1; // Activer les interruptions périphériques
}

#endif