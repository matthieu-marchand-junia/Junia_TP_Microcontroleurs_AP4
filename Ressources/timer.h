#include <xc.h>
#ifndef TIMER_H
#define	TIMER_H

#define TIMER2_FLAG PIR1bits.TMR2IF
#define TIMER2_ENABLE PIE1bits.TMR2IE

void config_timer2(int period, int prescaler, int postscaler);

void config_timer2_for_1ms(void);
void config_timer2_for_120ms(void);

void wait_timer2(void);
void start_timer2();

#endif