/*
Résultats obtenus : 

Dans un premier temps, nous avons obtenu un résultat précis 
à environ 72us en configurant le Timer2 à 124,928 ms. 

Ensuite, nous avons opté pour une solution plus précise en 
configurant le Timer2 à pile 1 ms. Nous utilisons le timer 
125 fois pour attendre précisément 125ms.

Cette seconde solution est plus précise car le temps d'éxécution des 
intructions (boucle, utilisation du timer) est < 72us.

Le chenillard a été mesuré avec un chronomètre.
*/ 

#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

// MCU : PIC16F1719 
//
// | LED   | Registre |
// |-------|----------|
// | D1-D4 | LATD     |
// | D5-D8 | LATB     |
//
// | LED | Registre       | Pin |
// |-----|----------------|-----|
// | D1  | LATDbits.LATD0 | R5  |
// | D2  | LATDbits.LATD1 | R6  |
// | D3  | LATDbits.LATD2 | R7  |
// | D4  | LATDbits.LATD3 | R8  |
// | D5  | LATBbits.LATB0 | R9  |
// | D6  | LATBbits.LATB1 | R10 |
// | D7  | LATBbits.LATB2 | R11 |
// | D8  | LATBbits.LATB3 | R12 |
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
Solution précise retenue :
Nous pouvons obtenir précisément 125 ms en attendant 125 fois un timer de 1000 us

Raisonnement pour trouver les valeurs :
Toverflow = (PR2 + 1) × ( (prescaler × postscaler) / (Fosc/4) )
On souhaite Toverflow ≃ 1 000 et on a Fosc = 8mHz.

Valeurs trouvées par recherche à tâton sur google sheet :
Avec PR2 = 249, prescaler = 1, postscaler = 8, on a Toverflow = 1 000.

Configurer le Timer2 avec une période de 1 000 us.
Soit 1 ms. */
void config_timer2(void){
 PR2 = 249; // Period register = 249
 T2CONbits.T2CKPS = 0b00; // Prescaler = 1:1
 T2CONbits.T2OUTPS = 0b0111; // Postscaler = 1:8
 T2CONbits.TMR2ON = 1; // Timer2 activé
}

/* Fonction d’attente bloquante utilisant le Timer2 */
void wait_1ms(void){
    while(!PIR1bits.TMR2IF){}
    PIR1bits.TMR2IF = 0;
}

void wait_125ms(void){
    for(int i = 0; i<125; i++) {
        wait_1ms();
    }
}

/* 
Solution approximative non retenue :
Nous ne pouvons pas avoir un timer qui fasse exactement 125 ms

Raisonnement pour trouver les valeurs :
Toverflow = (PR2 + 1) × ( (prescaler × postscaler) / (Fosc/4) )
On souhaite Toverflow ≃ 125 000 et on a Fosc = 8mHz.

Valeurs trouvées par recherche à tâton sur google sheet :
A) Avec PR2 = 244, prescaler = 64, postscaler = 16, on a Toverflow = 124 928.
Soit un écrat de 72.

B) Avec PR2 = 245, prescaler = 64, postscaler = 16, on a Toverflow = 124 928.
Soit un écrat de 440.

La solution A) est la plus précise. Le timer reste toutefois trop rapide de 72us.

Configurer le Timer2 avec une période de 124 928 us.
Soit 124,928 ms. */
// void config_timer2(void){
//  PR2 = 244; // Period register = 244
//  T2CONbits.T2CKPS = 0b11; // Prescaler = 1:64
//  T2CONbits.T2OUTPS = 0b1111; // Postscaler = 1:16
//  T2CONbits.TMR2ON = 1; // Timer2 activé
// }

// /* Fonction d’attente bloquante utilisant le Timer2 */
// void wait_125ms(void){
//  while(!PIR1bits.TMR2IF){}
//  PIR1bits.TMR2IF = 0;
// }