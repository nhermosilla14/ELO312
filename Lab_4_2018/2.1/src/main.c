#include <msp430x16x.h>
#include "osc.h"
#include "display.h"
void main(void)
{       unsigned int a;
        osc_init_xt2();
	WDTCTL = WDTPW + WDTHOLD;
	TBCCR0 = 65535;
	TBCTL = TBSSEL_2 + MC_1; 	// reloj de subsistema, modo up
        TBR = 0;
        udelay(0);
        a = TBR;
        TBR = 0;
        udelay(1);
        a = TBR;
        TBR =0;
        udelay(50);
        a = TBR;
        TBR = 0;
        udelay(100);
        a = TBR;
        TBR = 0;
        udelay(1000);
        a = TBR;
        TBR = 0;
}