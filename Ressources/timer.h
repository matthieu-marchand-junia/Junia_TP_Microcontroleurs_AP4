#include <xc.h>
#ifndef TIMER_H
#define	TIMER_H

#define TIMER2_FLAG PIR1bits.TMR2IF
#define TIMER2_ENABLE PIE1bits.TMR2IE

void config_timer2_for_1ms(void);
void wait_1ms(void);
void start_timer2();

#endif