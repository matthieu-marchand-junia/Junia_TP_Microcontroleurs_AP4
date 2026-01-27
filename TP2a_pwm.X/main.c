/*
 * File:   main.c
 * Author: maatt
 *
 * Created on January 20, 2026, 3:38 PM
 */


// Datasheet : https://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F1717_8_9-data-sheet-40001740C.pdf

// Stratégie de dev que l'on a suivi pour valider pas à pas notre avancée.
// 1. Allumer une led à 100% du cycle avec le PWM
// 2. Allumer une led à 10% du cycle avec le PWM
// 3. Allumer et éteindre une led avec le bouton
// 4. Allumer la led 100% ou 10% du cycle en fonction du bouton

// On suit la table Datasheet TABLE 17-2 p. 180 car Fosc = 8mHz
// Pour avoir un PWM period de 0.31 kHz
// PR2 = 0x65
// Prescale = 1:64 = 0b11
// Postscale = 1:1 = 0b0000
// Note : le postscaler n'est pas pris en compte pour le calcul 
// du cycle PWM, donc utilise le postscaler 1:1.

#include "../Ressources/configbits.h"
#include <xc.h>  
#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/button.h"
#include "../Ressources/button.c"
#include "../Ressources/timer.h"
#include "../Ressources/timer.c"

// Fonction pour assigner la valeur aux registres PWM4DCH:PWM4DCL<7:6>
void set_HL(int value) {
    PWM4DCH = value>>2;
    PWM4DCL = value<<6;
}

void main(void) {
    config_leds();

    config_button();

    // On suit la recette Datasheet 17.1.9 SETUP FOR PWM OPERATION USING PWMx PINS

    // 1. Disable the PWMx pin output driver(s) by setting the associated TRIS bit(s).
    // On veut allumer la LED D1 (port  RD0) de manière analogique
    // Donc il faut mettre TRISD0 en lecture (à 1)
    TRISDbits.TRISD0 = 1;

    // 2. Clear the PWMxCON register.
    // "Vous pourrez configurer votre signal à sur le module PWM4, dont la base de temps est par défaut générée par le Timer 2."
    // Donc on utilise le 4ème
    PWM4CON = 0;

    // 3. Load the PR2 register with the PWM period value
    PR2 = 0x65;

    // 4. Load the PWMxDCH register and bits <7:6> of the PWMxDCL register 
    // with the PWM duty cycle value.
    // D'après nos calcul, si on veut  PWM_duty_cycle = 10%, avec HL = PWMxDCH:PWMxDCL<7:6>
    // => 0,1 = HL / 4(PR2+1)
    // => HL = 0,1 * 4(PR2+1)
    // => HL = 40,8
    // HL étant un entier, on arrondi à 41 (0b00101001) pour être le plus proche des 10%
    // On a manuellement baissé à 10 pour que la différence soit notable à l'oeil.
    char HL_10_PERCENT=10;

    // si on veut PWM_duty_cycle = 100%, avec HL = PWMxDCH:PWMxDCL<7:6>
    // => 1 = HL / 4(PR2+1)
    // => HL = 1 * 4(PR2+1)
    // => HL = 408
    char HL_100_PERCENT = 408;
    
    set_HL(HL_100_PERCENT);

    // 5. Configure and start Timer2
    config_timer2(PR2, 0b11, 0b0000);

    // 6.  Enable PWM output pin and wait until Timer2 overflows, TMR2IF bit of the PIR1 register is set.
    // Note : For operation with other peripherals only, disable PWMx pin outputs.
    // Rien à faire dans notre cas

    // 7.  Enable the PWMx pin output driver(s) by clearing the associated TRIS bit(s) and 
    // setting the desired pin PPS control bits PWMxCON register with the appropriate values.
    // Connecter PWM4OUT à la led D1 (RD0)
    TRISDbits.TRISD0 = 0;
    RD0PPS = 0b01111;

    // 8. Configure the PWM module by loading the
    PWM4EN = 1; // Activer le module
    PWM4OUT = 0; // On laisse tel quel
    PWM4POL = 0; // PWM output is active high
    
    set_leds(0);

    while(1) {
        // 9. Ajuster le PWM4DCH pour aller à 10% ou 100%
        if(BTN_S1) {
            set_HL(HL_100_PERCENT);
        } else {
            set_HL(HL_10_PERCENT);
        }
    };
}