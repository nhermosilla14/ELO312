#include "msp430_version.h"
#include <stdio.h>
#include "display.h"
#include "osc.h"
#include "adc.h"

int d;

void main(void)
{
    osc_init_xt2();
    WDTCTL = WDTPW + WDTHOLD;

    display_init();

    CCTL0 = CCIE;             	// CCR0 habilita interrupción del timer
    CCR0 = 32768-1;

    TACTL = TASSEL_1 + MC_1 + ID_0;    // reloj ACLK, modo up to CCR0

    adc_init_single_channel_single_conv_it();

    _BIS_SR(LPM0_bits + GIE);	// modo bajo consumo

    // Interrupciones
}


#define CONV(x)      3.28*x/3848.0			// convertir x en voltaje

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
        
	CCTL0 = 0x00;
	adc_single_channel_single_conv_it(0);
	
}

#pragma vector = TIMERB0_VECTOR
__interrupt void Timer_B (void)
{

}


/**************************************************
* Nombre    		: __interrupt void adc_ADC12_interrupt(void)
* returns			: void
* Creada por		: Mauricio Solis
* Fecha creación	: 01/01/2013
* Descripción		: Vector de interrupciones del
ADC.
**************************************************/
#pragma vector = ADC12_VECTOR
__interrupt void adc_ADC12_interrupt(void)
{
    int pos = display_get_pos();
    printf("Vol=%1.3f\n", CONV(d));
    display_set_pos(pos);
    CCTL0 = CCIE;
}
                                    //
////////////////////////////////////////

