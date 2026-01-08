// Résultats obtenus : les 4 premières et dernières leds s'allument à un intervalle d'environ 1s

#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

// Allume les LEDs D1-8 de la carte Microchip Explorer 8 
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

void allumer_que_d1_a_d4(void);
void allumer_que_d5_a_d8(void);
void delai_approx(void);

void main(void) {
    TRISD &= 0xF0;
    TRISB &= 0xF0;

    while(1) {
        allumer_que_d1_a_d4();
        delai_approx();
        allumer_que_d5_a_d8();
        delai_approx();
    };
}

void delai_approx(void) {
    for (long i = 0; i < 90000; i++);
}

void allumer_que_d1_a_d4(void) {
    LATB  &= 0xF0;
    LATD  |= 0x0F;
}

void allumer_que_d5_a_d8(void) {
    LATD  &= 0xF0;
    LATB  |= 0x0F;
}