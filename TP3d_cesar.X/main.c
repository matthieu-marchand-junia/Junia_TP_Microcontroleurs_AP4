#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> // Pour tolower()

#include "../Ressources/configbits.h"
#include "../Ressources/spi.h"
#include "../Ressources/spi.c"
#include "../Ressources/lcd.h"
#include "../Ressources/lcd.c"
#include "../Ressources/pot.h"
#include "../Ressources/pot.c"
#include "../Ressources/serial.h"
#include "../Ressources/serial.c"

// Définitions
#define ALPHABET "0123456789abcdefghijklmnopqrstuvwxyz"
#define ALPHABET_SIZE 36
#define BUTTON PORTBbits.RB0 // S1 est sur RB0

// Prototypes
int get_alphabet_index(char c);

void main(void) {
    char alphabet[] = ALPHABET;
    int offset = 0;
    int mode = 0; // 0 = Chiffrement, 1 = Déchiffrement
    char buffer_lcd[16];
    
    // Initialisations
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    config_pot();
    
    init_serial();
    init_baudrate();
    enable_eusart();
    
    // Config Bouton (RB0 en entrée numérique)
    TRISBbits.TRISB0 = 1;
    ANSELBbits.ANSB0 = 0;

    LCD_Clear();

    while (1) {
        // 1. Lecture du potentiomètre pour l'offset (0 à 35)
        // On mappe la valeur 0-255 vers 0-35
        offset = (read_pot() * (ALPHABET_SIZE - 1)) / 255;

        // 2. Gestion du bouton pour le mode (Toggle)
        if (BUTTON == 0) { // Si appuyé
            mode = !mode;
            while(BUTTON == 0); // Anti-rebond simple
        }

        // 3. Mise à jour de l'écran LCD
        LCD_GoTo(0, 0);
        sprintf(buffer_lcd, "Mode: %s", mode ? "Decrypt" : "Encrypt");
        LCD_WriteString(buffer_lcd);
        
        LCD_GoTo(1, 0);
        sprintf(buffer_lcd, "Offset: %02d     ", offset);
        LCD_WriteString(buffer_lcd);

        // 4. Traitement UART (si un caractère est reçu)
        if (PIR1bits.RCIF) {
            char incoming = tolower(UART_Read());
            int idx = get_alphabet_index(incoming);

            // Les caractères hors alphabet sont ignorés selon la consigne
            if (idx == -1) {
                continue
            }

            int new_idx;
            if (mode == 0) { 
                // Chiffrement
                new_idx = (idx + offset) % ALPHABET_SIZE;
            } else { 
                // Déchiffrement
                new_idx = (idx - offset + ALPHABET_SIZE) % ALPHABET_SIZE;
            }
            
            UART_Write(alphabet[new_idx]);
        }
    }
}

// --- Fonctions Utilitaires ---
int get_alphabet_index(char c) {
    char *list = ALPHABET;
    char *ptr = strchr(list, c);
    if (ptr) return (int)(ptr - list);
    return -1; // Non trouvé
}