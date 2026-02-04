#ifndef _LEDS_H_
#define	_LEDS_H_

#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define LED4 LATDbits.LATD3
#define LED5 LATBbits.LATB0
#define LED6 LATBbits.LATB1
#define LED7 LATBbits.LATB2
#define LED8 LATBbits.LATB3

void config_leds(void);
void set_leds(unsigned char value);
void set_led(int led, unsigned char);
void led_from_pps(int output_led, char input_device);

#endif