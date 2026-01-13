/*
Résultats obtenus : 

Plutôt que de faire attendre le programme 125 ms, nous souhaitons utiliser 
les interruptions pour mettre à jour le chenillard.

Nous devons conserver la précision de 125 ms, donc réutiliser le timer de 
1 ms obtenu au 1.c.

Nous ré-utilisons donc le système de postscaler, en incrémentant une variable 
à chaque interruption (1 ms), pour mettre à jour le chenillard au bout
de 125 interruptions (125 ms).

Comme il n'y a pas de fonction d'attente entre chaque led, la led actuellement allumée 
est stockée dans une variable. Elle permet d'éteindre la led allumée et d'allumer la 
suivante.
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

void config_interrupt(void);
void config_leds(void);
void config_timer2(void);

void handle_timer_interruption(void);
void update_chenillard(void);

void set_leds(unsigned char value);
void set_led(int led, unsigned char);

int counter_ms = 0;
int led = 8;

void main(void) {
    config_leds();
    config_interrupt();
    config_timer2();

    set_leds(0);

    while(1);
}

void config_interrupt(void) {
    INTCONbits.GIE = 1; // Activer les interruptions globales
    INTCONbits.PEIE = 1; // Activer les interruptions périphériques
    PIE1bits.TMR2IE = 1; // Activer l'interruption TIMER2
    PIR1bits.TMR2IF = 0; // Initialiser le flag TIMER2 pour attendre l'interruption
}

void config_leds(void) {
    TRISD &= 0xF0; // Configuration des leds D1 à D4
    TRISB &= 0xF0; // Configuration des leds D5 à D8
}

/*
Configurer le Timer2 avec une période de 1 000 us.
Soit 1 ms. 

Voir ../TP1c_timer.X/main.c#config_timer2
*/
void config_timer2(void) {
 PR2 = 249; // Period register = 249
 T2CONbits.T2CKPS = 0b00; // Prescaler = 1:1
 T2CONbits.T2OUTPS = 0b0111; // Postscaler = 1:8
 T2CONbits.TMR2ON = 1; // Timer2 activé
}

void __interrupt() timer_handler (void){
    if (PIE1bits.TMR2IE && PIR1bits.TMR2IF){
        PIR1bits.TMR2IF = 0; // Ré-initialiser le flag TIMER2 pour attendre l'interruption
        
        handle_timer_interruption();
    }
}

void handle_timer_interruption(void) {
    if(++counter_ms >= 125) {
        counter_ms = 0; // Réinitialiser le compteur

        update_chenillard();
    }
}

void set_leds(unsigned char value) {
    // D1 à D4
    LATBbits.LATB3 = value;
    LATBbits.LATB2 = value;
    LATBbits.LATB1 = value;
    LATBbits.LATB0 = value;

    // D5 à D8
    LATDbits.LATD3 = value;
    LATDbits.LATD2 = value;
    LATDbits.LATD0 = value;
    LATDbits.LATD1 = value;
}

void set_led(int led, unsigned char value) {
    switch(led)
    {
        case 1:
            LATDbits.LATD0 = value;
            break;
        case 2:
            LATDbits.LATD1 = value; 
            break;
        case 3:
            LATDbits.LATD2 = value; 
            break;
        case 4:
            LATDbits.LATD3 = value; 
            break;
        case 5:
            LATBbits.LATB0 = value;
            break;
        case 6:
            LATBbits.LATB1 = value; 
            break;
        case 7:
            LATBbits.LATB2 = value; 
            break;
        case 8:
            LATBbits.LATB3 = value; 
            break;
    }
}

// Fonction qui éteint la led actuellement allumée et qui allume la led suivante
void update_chenillard(void) {
    set_led(led, 0);

    // Incrémenter la led, retour à la première led si on a atteint la dernière
    if(++led>8) { 
        led = 1; 
    }

    set_led(led, 1);
}

