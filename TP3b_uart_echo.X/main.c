#include <xc.h>
#include "../Ressources/configbits.h"

void init_serial(void) {
    RC6PPS = 0b00010100;
    RXPPS = 0b00010111;
    TRISCbits.TRISC6 = 0; 
    ANSELCbits.ANSC7 = 0;
    TRISCbits.TRISC7 = 1;
}

void init_baudrate(void) {
    TX1STAbits.SYNC = 0;
    TX1STAbits.BRGH = 0;
    BAUD1CONbits.BRG16 = 0;
    SP1BRGL = 12;
    SP1BRGH = 0;
}

void enable_eusart(void) {
    RC1STAbits.SPEN = 1; 
    TX1STAbits.TXEN = 1;
    RC1STAbits.CREN = 1;
}

void UART_Write(char data) {
    while (PIR1bits.TXIF == 0);
    TX1REG = data;
}

void __interrupt() my_isr(void) {
    if (PIR1bits.RCIF) {
        UART_Write(RC1REG);
        UART_Write('.');
    }
}

void main(void) {
    init_serial();
    init_baudrate();
    enable_eusart();
    
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1) {}
}