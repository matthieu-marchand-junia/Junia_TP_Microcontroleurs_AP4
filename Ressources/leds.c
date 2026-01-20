#include <xc.h>
#include "leds.h"

void config_leds(void) {
    TRISD &= 0xF0; // Configuration des leds D1 à D4
    TRISB &= 0xF0; // Configuration des leds D5 à D8
}

void set_leds(unsigned char value) {
    LED8 = value;
    LED7 = value;
    LED6 = value;
    LED5 = value;
    LED4 = value;
    LED3 = value;
    LED2 = value;
    LED1 = value;
}

void set_led(int led, unsigned char value) {
    switch(led)
    {
        case 1:
            LED1 = value;
            break;
        case 2:
            LED2 = value; 
            break;
        case 3:
            LED3 = value; 
            break;
        case 4:
            LED4 = value; 
            break;
        case 5:
            LED5 = value;
            break;
        case 6:
            LED6 = value; 
            break;
        case 7:
            LED7 = value; 
            break;
        case 8:
            LED8 = value; 
            break;
    }
}