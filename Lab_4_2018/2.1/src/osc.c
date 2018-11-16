#include "msp_version.h"
void osc_init_xt2(void)
{
	// Al enceder la MSP, ésta queda operando a aprox 800kHz para MCLK y SMCLK,
	// y a XT1 en modo LF para ACLK

	BCSCTL1 &= ~XT2OFF;                            // XT2 encendido (8MHz)
	do                                             // wait in loop until crystal is stable
		IFG1 &= ~OFIFG;
	while (IFG1 & OFIFG);
	IE1 &= ~WDTIE;                                 // disable WDT int.
	IFG1 &= ~WDTIFG;                               // clear WDT int. flag

	BCSCTL2 = SELM_2 | DIVM_0 | SELS | DIVS_0 ;    // MCLK <- XT2 | MCLK = 1:1 | SMCLK <- XT2 | SMCLK = 1:1 ;

	WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDTIS1 ; // use WDT as timer, flag each 512 pulses from SMCLK
	while (!(IFG1 & WDTIFG));                       // count 1024 pulses from XT2
	// (until XT2's amplitude is OK)
	IFG1 &= ~OFIFG;                                 // clear osc. fault int. flag
}

