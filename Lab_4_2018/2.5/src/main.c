#include "msp430_version.h"
#include <stdio.h>
#include "display.h"
#include "osc.h"

unsigned int cycles = 0;
unsigned int seconds = 0;
unsigned int minutes = 0;
unsigned char dots = ':';

void main(void)
{
  /* Inicializaciones */
	osc_init_xt2();
        display_init();
	WDTCTL = WDTPW + WDTHOLD;
	TACCTL0 = CCIE;              // CCR0 habilita interrupción del timer
	TACCR0 = 50000;
	TACTL = TASSEL_1 + MC_1 +ID_3 ;   // reloj auxiliar, modo up to CCR0
/* Configuración de pantalla */
        display_set_pos(0);
        
/* Variables */
        
        while(1){
          display_clear();
        display_set_pos(0);
          printf("      %d%c%d     ", minutes, dots, seconds);
        _BIS_SR(LPM0_bits + GIE);
        }
	  // modo bajo consumo


    // interrupciones
}

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
        cycles++;
        if ((cycles % 10) == 0){
          if (dots == '\0')
            dots == ':';
          else
            dots == '\0';
        }
        seconds = cycles % 20;
        minutes = seconds % 60;
}

