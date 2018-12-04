#include "msp430_version.h"            // Depende del uC que Ud. esté ocupando.
#include "uart.h"
#include "display.h"
#include "tic.h"

char mensaje[10] = "Hola Mundo";
int i = 0,j = 0;

void main(void) {
	// osc_init_xt2();
	
	WDTCTL = WDTPW + WDTHOLD;
        _BIS_SR(GIE);
        display_init();
        display_clear();
        keyboard_init();
        tic_init();
	P5SEL |= 0x70;                     // Se dispone de los 3 relojes del sistema
	P5DIR |= 0x70;                     // en los bits 4, 5 y 6 de la puerta 5
	                                   // (MCLK, SMCLK y ACLK)
        UCTL0 &= (~BIT7 | ~BIT5 | ~BIT2); // paridad desahabilitada, 1 stop, UART
        UCTL0 |= BIT4; // 8bits
   //     UCTL0 |= BIT3; // loopback
	uart_0_init_p2();
	_EINT();                    		// Habilita las interrupciones
}
