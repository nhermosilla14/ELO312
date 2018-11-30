#include "msp430_version.h"
#include "keyboard.h"
#include "display.h"
#include "tic.h"


void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  display_init();
  keyboard_init();
  tic_init();
  _BIS_SR(GIE);  
}

