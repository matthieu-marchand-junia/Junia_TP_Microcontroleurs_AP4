#include <xc.h>
#include "configbits.h"

/*
Le module PPS (RC6PPS, RXPPS) connecte le module
de communication aux pattes RC6 et RC7
*/
void init_serial(void) {
    RC6PPS = 0x14; 
    RXPPS = 0x17;  

    // RC6 en output
    LATCbits.LATC6 = 0;
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

void init_all(void){
    init_serial();
    init_baudrate();
    enable_eusart();
}

// Attend que le buffer soit vide avant de poser une lettre dedans.
void UART_Write(char data) {
    while (PIR1bits.TXIF == 0) {}
    TX1REG = data;
}

// Envoie RC1REG contenant la valeur complète des données envoyés à TX1REG
char UART_Read(void) {
    while (PIR1bits.RCIF == 0) {}
    return RC1REG;
}

// Boucle qui prend une phrase et appelle UART_Write pour chaque lettre une par une.
void display_text(char *str) {
    while (*str != '\0') {
        UART_Write(*str);
        str++;
    }
    UART_Read();
}

void main(void) {
    init_all();
    
    while (1) {
        display_text("Hello, World!");
    }
}