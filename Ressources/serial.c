#include <xc.h>
#include "serial.h"

#ifndef _SERIAL_C_
#define _SERIAL_C_

/*
Le module PPS (RC6PPS, RXPPS) connecte le module
de communication aux pattes RC6 et RC7
*/
void init_serial(void) {
    RC6PPS = 0b00010100;
    RXPPS = 0b00010111;

    // RC6 en output
    LATCbits.LATC6 = 1;
    TRISCbits.TRISC6 = 0;  
    
    // RC7 en input
    ANSELCbits.ANSC7 = 0;
    TRISCbits.TRISC7 = 1;
}

// Permet que les deux appareils parles à la même vitesse (9600 bits par seconde)
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

// Attend que le buffer soit vide avant de poser une lettre dedans.
void UART_Write(char data) {
    while (PIR1bits.TXIF == 0) {}
    TX1REG = data;
}

// Envoie RC1REG contenant la valeur complète des données envoyés à TX1REG
char UART_Read(void) {
    // while (PIR1bits.RCIF == 0) {}
    return RC1REG;
}

#endif