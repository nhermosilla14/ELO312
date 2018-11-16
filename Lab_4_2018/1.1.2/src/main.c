#include "msp430_version.h"
#include <stdio.h>
#include "display.h"
#include "osc.h"

int line = 0;
int sec = 0;

void main(void)
{
	osc_init_xt2();
	WDTCTL = WDTPW + WDTHOLD;
	display_init();

	TACCTL0 = CCIE;              // CCR0 habilita interrupci�n del timer
	TACCR0 = 32768 >> 2;

	TACTL = TASSEL_1 + MC_1;   // reloj auxiliar, modo up to CCR0
	display_test_Write_CGRAM_MS();
	display_set_pos(0x00);
	printf("LAB ELO312");
	printf("%c",0x01);
        printf("\r");
        printf("\n");
        printf("\t");
        printf("\b");

	_BIS_SR(LPM0_bits + GIE);  // modo bajo consumo


    // interrupciones
}

// Timer A0 rutina de servicio de interrupci�n
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	P2OUT ^= 0x1;
}

