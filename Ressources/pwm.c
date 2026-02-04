#include <xc.h>
#include "pwm.h"
#include "timer.h"
#include "timer.c"

#ifndef _PWM_C_
#define _PWM_C_

void set_pwm_percentage(int percentage) {
    // D'après nos calcul, si on veut  PWM_duty_cycle = percentage, avec PWMxDCH
    // On a PWM_duty_cycle = PWMxDCH / (PR2+1)
    // => percentage/100 = PWMxDCH / (PR2+1)
    // => PWMxDCH = percentage/100 * (PR2+1)
    
    // Comme c'est un int, on divise par 100 à la fin seulement
    // Sinon, la division par 100 va tronquer et fausser le résultat
    PWM4DCH = percentage * (PR2+1) /100;
    PWM4DCL = 0b00;
}

void config_pwm(void) {
    // On souhaite utiliser le timer de 1ms
    // Donc 100% = 1ms
    // 1% = 0,01ms
    
    // On suit la recette Datasheet 17.1.9 SETUP FOR PWM OPERATION USING PWMx PINS

    // 1. Disable the PWMx pin output driver(s) by setting the associated TRIS bit(s).
    // On veut allumer la LED D1 (port  RD0) de manière analogique
    // On se rend compte expérimentalement que cette étape ne nous sert pas.    

    // 2. Clear the PWMxCON register.
    // "Vous pourrez configurer votre signal à sur le module PWM4, dont la base de temps est par défaut générée par le Timer 2."
    // Donc on utilise le 4ème
    PWM4CON = 0;

    // 3. Load the PWMxDCH register and bits <7:6> of the PWMxDCL register 
    // with the PWM duty cycle value.
    set_pwm_percentage(100);

    // 4. Configure and start Timer2
    config_timer2_for_1ms();
    start_timer2();

    // 5.  Enable PWM output pin and wait until Timer2 overflows, TMR2IF bit of the PIR1 register is set.
    // Note : For operation with other peripherals only, disable PWMx pin outputs.
    // Rien à faire dans notre cas

    // 6.  Enable the PWMx pin output driver(s) by clearing the associated TRIS bit(s) and 
    // setting the desired pin PPS control bits PWMxCON register with the appropriate values.
    // À configurer avant d'appeler cette fonction
    // Utiliser led_from_pps()

    // 8. Configure the PWM
    PWM4EN = 1; // Activer le module
}

#endif