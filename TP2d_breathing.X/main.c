#include "../Ressources/configbits.h"
#include <xc.h>  

#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/interrupt.h"
#include "../Ressources/interrupt.c"
#include "../Ressources/timer.h"
#include "../Ressources/timer.c"
#include "../Ressources/pwm.h"
#include "../Ressources/pwm.c"

void config_pps() {
    RD0PPS = 15;
}

int percentage = 0;
int count = 0;
int direction=1;

void __interrupt() isr(void) {
    if(TMR2IE && TMR2IF) {
        TMR2IF = 0;

        count++;

        if(count >=10) {
            count = 0;
            percentage+=direction;
        }

        if(percentage >= 100) direction = -1;
        if(percentage <= 0) direction = 1;

        set_pwm_percentage(percentage);
    }
}

void main(void) {
    config_leds();
    config_pwm();
    config_interrupt();
    config_pps();

    while(1);
}
