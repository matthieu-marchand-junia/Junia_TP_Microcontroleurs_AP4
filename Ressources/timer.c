#include <xc.h>
#include "timer.h"

void config_timer2_for_1ms(void) {
 PR2 = 249; // Period register = 249
 T2CONbits.T2CKPS = 0b00; // Prescaler = 1:1
 T2CONbits.T2OUTPS = 0b0111; // Postscaler = 1:8
 T2CONbits.TMR2ON = 1; // Timer2 activé
}

void wait_1ms(void) {
    while(!TIMER2_FLAG){}
    TIMER2_FLAG = 0;
}

void start_timer2() {
    TIMER2_ENABLE = 1; // Activer l'interruption TIMER2
    TIMER2_FLAG = 0; // Initialiser le flag TIMER2 pour attendre l'interruption
}
 