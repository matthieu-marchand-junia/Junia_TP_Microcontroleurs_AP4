// Résultats obtenus : 

#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

// MCU : PIC16F1719 
//
// | LED | Pin |
// |-----|-----|
// |  D1 | R5 |
// |  D2 | R6 |
// |  D3 | R7 |
// |  D4 | R8 |
// |  D5 | R9 |
// |  D6 | R10 |
// |  D7 | R11 |
// |  D8 | R12 |
//

void allumer_chenillard(void);
void config_timer2(void);
void wait_125ms(void);

void main(void) {
    TRISD &= 0xF0; // Configuration des leds D1 à D4
    TRISB &= 0xF0; // Configuration des leds D5 à D8
    LATD  &= 0xF0; // éteindre leds de d1 à d4
    LATB  &= 0xF0;  // éteindre leds de d5 à d8

    config_timer2();

    while(1) {
        allumer_chenillard();
    };
}


void allumer_chenillard(void) {
    LATD  &= 0xF0; // éteindre leds de d1 à d4
    LATDbits.LATD0 = 1;
    wait_125ms();
    LATD  &= 0xF0;
    LATDbits.LATD1 = 1;
    wait_125ms();
    LATD  &= 0xF0;
    LATDbits.LATD2 = 1;
    wait_125ms();
    LATD  &= 0xF0;
    LATDbits.LATD3 = 1;
    wait_125ms();
    LATD  &= 0xF0;

    LATB  &= 0xF0;  // éteindre leds de d5 à d8
    LATBbits.LATB0 = 1;
    wait_125ms();
    LATB  &= 0xF0;
    LATBbits.LATB1 = 1;
    wait_125ms();
    LATB  &= 0xF0;
    LATBbits.LATB2 = 1;
    wait_125ms();
    LATB  &= 0xF0;
    LATBbits.LATB3 = 1;
    wait_125ms();
    LATB  &= 0xF0;
}

/* 
Toverflow = (PR2 + 1) × ( (prescaler × postscaler) / (Fosc/4) )
On souhaite Toverflow ≃ 125 000 et on a Fosc = 8mHz.

Toverflow = (PR2 + 1) × ( (prescaler × postscaler) / (Fosc/4) )
On souhaite Toverflow ≃ 125 000 et on a Fosc = 8mHz.

A) Avec PR2 = 244, prescaler = 64, postscaler = 16, on a Toverflow = 124 928.
Soit un écrat de 72.

B) Avec PR2 = 245, prescaler = 64, postscaler = 16, on a Toverflow = 124 928.
Soit un écrat de 440.

Nous conservons donc la solution A).

Configurer le Timer2 avec une période de 125 000 us, soit 125 ms 
*/
void config_timer2(void) {
 PR2 = 244; // Period register = 244
 T2CONbits.T2CKPS = 0b11; // Prescaler = 1:64
 T2CONbits.T2OUTPS = 0b1111; // Postscaler = 1:16
 T2CONbits.TMR2ON = 1; // Timer2 activé
}

/* Fonction d’attente bloquante utilisant le Timer2 */
void wait_125ms(void) {
 while(!PIR1bits.TMR2IF){}
 PIR1bits.TMR2IF = 0;
}