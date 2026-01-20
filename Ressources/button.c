#include <xc.h>
#include "button.h"

void config_button(void) {
    TRISBbits.TRISB0 = 1; // Configuer le port du bouton S1 en lecture
}