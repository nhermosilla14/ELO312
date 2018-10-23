#include  "msp430_version.h"

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= 0x01;			// P1.0 salida
	TACCTL0 = CCIE;			// TACCR0 habilita interrupción del timer
	TACCR0 = 500;
	TACTL = TASSEL_2 + MC_1; 	// reloj de subsistema, modo up
	_BIS_SR(GIE); 	// modo bajo consumo e interrupciones
}

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= 0x0F; // Toggle P1.0
}

