#include <xc.h>
#include "interrupt.h"

void config_interrupt(void) {
    INTCONbits.GIE = 1; // Activer les interruptions globales
    INTCONbits.PEIE = 1; // Activer les interruptions périphériques
}