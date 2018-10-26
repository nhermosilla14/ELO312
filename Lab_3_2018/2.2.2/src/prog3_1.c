#include  "msp430_version.h"
#define MAX 500
/***************************************
 * Frecuencia de salida 10 veces menor *
 * ajustada subiendo el MAX (contador  *
 * para el soft delay).                *
 ***************************************/
void main(void) 
{  
	WDTCTL = WDTPW + WDTHOLD;  	// Detiene el timer watchdog  
	P1DIR |= BIT0;			// pin 0 puerto 1 es salida
 
	while(1)                               
	{ 
		unsigned int i; 

		P1OUT ^= BIT0;		// toggle del bit 0 puerto 1

		for (i = 0; i < MAX; i++); // software delay
	} 
}
