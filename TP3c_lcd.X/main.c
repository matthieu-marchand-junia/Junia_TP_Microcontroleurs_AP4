#include <xc.h>
#include "../Ressources/configbits.h"
#include "../Ressources/spi.h"
#include "../Ressources/spi.c"
#include "../Ressources/lcd.h"
#include "../Ressources/lcd.c"

#define SCROLL_SPEED 20000 

void main(void) {
    char message[] = "                 Hello, World !                 ";
    int i = 0;

    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();

    while (1) {
        LCD_Clear();
        LCD_GoTo(0, 0);
        
        // On affiche une portion du message à partir de l'indice i
        // Le pointeur avance dans la chaîne de caractères
        LCD_WriteString(&message[i]); 
        
        // Délai pour que l'oeil humain puisse lire
        for(unsigned long d=0; d < SCROLL_SPEED; d++); 

        i++;
        
        // Si on arrive à la fin du message
        // On recommence au début
        if (message[i + 16] == '\0') {
            i = 0;
        }
    }
}