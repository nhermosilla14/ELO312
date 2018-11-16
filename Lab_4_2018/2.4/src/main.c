#include "msp430_version.h"
#include <stdio.h>
#include "display.h"
#include "osc.h"

int line = 0;
int sec = 0;

/************      NUEVO JUEGO DE CARACTERES        ********************/
char new_char1[]={0x0,0x0,0x0,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};
char new_char2[]={0x0,0x0,0x0,BIT2,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};
char new_char3[]={0x0,BIT2,0x0,BIT2,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};
char new_char4[]={BIT2,0x0,BIT2,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};
char new_char5[]={0x0,BIT2,0x0,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};
char new_char6[]={BIT2,0x0,0x0,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};
/***********************************************************************/

void main(void)
{
	osc_init_xt2();
	WDTCTL = WDTPW + WDTHOLD;
	display_init();

	TACCTL0 = CCIE;              // CCR0 habilita interrupción del timer
	TACCR0 = 32768 >> 2;

	TACTL = TASSEL_1 + MC_1;   // reloj auxiliar, modo up to CCR0
	display_test_Write_CGRAM_MS();
	display_set_pos(0x00);
        display_add_new_character_CGRAM(2, new_char1);
        display_add_new_character_CGRAM(3, new_char2);
        display_add_new_character_CGRAM(4, new_char3);
        display_add_new_character_CGRAM(5, new_char4);
        display_add_new_character_CGRAM(6, new_char5);
        display_add_new_character_CGRAM(7, new_char6);
	printf("LAB ELO312");
        for (int i = 2; i < 8; i++){
            printf("\b%c", i);
        }
	_BIS_SR(LPM0_bits + GIE);  // modo bajo consumo


    // interrupciones
}

// Timer A0 rutina de servicio de interrupción
#pragma vector = TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	P2OUT ^= 0x1;
}

