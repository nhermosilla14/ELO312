#include  "msp430_version.h"

/**********************************
 *      VERSION MODIFICADA        *
 **********************************/

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;

	P2DIR |= 0x08;			// P2.3 salida -> 0000 1000
	TACCTL0 = CCIE;			// TACCR0 habilita interrupción del timer
	TACCR0 = 500;
// La siguiente l�nea setea el reloj de subsistema y modo up -> cuenta hasta TACCR0        
	TACTL = TASSEL_2 + MC_1; 	// reloj de subsistema, modo up
	_BIS_SR(LPM0_bits + GIE); 	// modo bajo consumo e interrupciones
}

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	P1OUT ^= 0x0F; // Toggle P2.3
}

