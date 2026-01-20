/*
Résultats obtenus : 

L'avantage de l'interruption est nettement visible : 
les deux chenillards cohabitent parfaitement. 

Le chenillard à interruption n'est pas impacté par la routine
lente et bloquante du second chenillard.
*/ 

#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC
#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/timer.h"
#include "../Ressources/timer.c"
#include "../Ressources/interrupt.h"
#include "../Ressources/interrupt.c"

// MCU : PIC16F1719 

void handle_timer_interruption(void);
void update_chenillard(void);

void delai_approx_1s(void);

int counter_ms = 0;
int led = 4;

void main(void) {
    config_leds();
   
    config_interrupt();
    config_timer2_for_1ms();

    start_timer2();

    set_leds(0);

    while(1) { // Chenillard lent et bloquant (D8 à D5)
        set_led(5, 0);
        set_led(8, 1);

        delai_approx_1s();

        set_led(8, 0);
        set_led(7, 1);

        delai_approx_1s();

        set_led(7, 0);
        set_led(6, 1);

        delai_approx_1s();

        set_led(6, 0);
        set_led(5, 1);

        delai_approx_1s();
    };
    while(1);
}

void __interrupt() timer_handler (void){
    if (TIMER2_ENABLE && TIMER2_FLAG){
        TIMER2_FLAG = 0; // Ré-initialiser le flag TIMER2 pour attendre l'interruption
        
        handle_timer_interruption();
    }
}

void handle_timer_interruption(void) {
    if(++counter_ms >= 125) {
        counter_ms = 0; // Réinitialiser le compteur

        update_chenillard();
    }
}

// Fonction qui éteint la led actuellement allumée et qui allume la led suivante
void update_chenillard(void) {
    set_led(led, 0);

    // Incrémenter la led, retour à la première led si on a atteint la dernière
    if(++led>4) { 
        led = 1; 
    }

    set_led(led, 1);
}

// Attendre approximativement 1s
void delai_approx_1s(void) {
    for (long i = 0; i < 90000; i++); // Obtenu expérimentalement
}
