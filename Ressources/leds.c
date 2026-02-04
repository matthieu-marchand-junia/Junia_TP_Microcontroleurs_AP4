#include <xc.h>
#include "leds.h"

#ifndef _LEDS_C_
#define	_LEDS_C_

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

// Sélectionner input_device depuis la table TABLE 12-2 p.154
// https://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F1717_8_9-data-sheet-40001740C.pdf
void set_led_from_pps(int output_led, char input_device) {
    switch (output_led) {
        case 1:    
            TRISDbits.TRISD0 = 0;
            RD0PPS = input_device;
            break;
        case 2:
            TRISDbits.TRISD1 = 0;
            RD1PPS = input_device;
            break;
        case 3:
            TRISDbits.TRISD2 = 0;
            RD2PPS = input_device;
            break;
        case 4:
            TRISDbits.TRISD3 = 0;
            RD3PPS = input_device;
            break;
        case 5:
            TRISBbits.TRISB0 = 0;
            RB0PPS = input_device;
            break;
        case 6:
            TRISBbits.TRISB1 = 0;
            RB1PPS = input_device;
            break;
        case 7:
            TRISBbits.TRISB2 = 0;
            RB2PPS = input_device;
            break;
        case 8:
            TRISBbits.TRISB3 = 0;
            RB3PPS = input_device;
            break;
    }
}

#endif