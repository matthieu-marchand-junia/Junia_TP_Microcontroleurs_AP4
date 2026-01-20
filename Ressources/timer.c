#include <xc.h>
#include "timer.h"

/**
Time = (Period + 1) * ( (Prescaler * Postscaler) / (Fosc/4) ) µs

Fosc = 8

Period : between 1 and 255 (included)

Prescaler values :
11 = Prescaler is 64
10 = Prescaler is 16
01 = Prescaler is 4
00 = Prescaler is 1

Postscaler values :
1111 = 1:16 Postscaler
1110 = 1:15 Postscaler
1101 = 1:14 Postscaler
1100 = 1:13 Postscaler
1011 = 1:12 Postscaler
1010 = 1:11 Postscaler
1001 = 1:10 Postscaler
1000 = 1:9 Postscaler
0111 = 1:8 Postscaler
0110 = 1:7 Postscaler
0101 = 1:6 Postscaler
0100 = 1:5 Postscaler
0011 = 1:4 Postscaler
0010 = 1:3 Postscaler
0001 = 1:2 Postscaler
0000 = 1:1 Postscaler

*/
void config_timer2(int period, int prescaler, int postscaler) {
    PR2 = period; // Period register = 249
    T2CONbits.T2CKPS = prescaler; // Prescaler = 1:1
    T2CONbits.T2OUTPS = postscaler; // Postscaler = 1:8
    T2CONbits.TMR2ON = 1; // Timer2 activé
}

void config_timer2_for_1ms(void) {
    config_timer2(249, 0b00, 0b0111)
}

void config_timer2_for_120ms(void) {
    config_timer2(249, 0b11, 0b1110)
}

void config_timer2_for_1ms(void) {
    config_timer2(249, 0b00, 0b0111)
}

void wait_timer2(void) {
    while(!TIMER2_FLAG){}
    TIMER2_FLAG = 0;
}

void start_timer2() {
    TIMER2_ENABLE = 1; // Activer l'interruption TIMER2
    TIMER2_FLAG = 0; // Initialiser le flag TIMER2 pour attendre l'interruption
}
 