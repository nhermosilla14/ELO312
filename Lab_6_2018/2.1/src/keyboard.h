#ifndef __button_matrix
#define __button_matrix
/*  Include section
*
***************************************************/
#include "msp430_version.h"

/*  Defines section
*
***************************************************/
#define PTOUT 			P2OUT
#define PTIN 			P2IN
#define PTDIR 			P2DIR

#define MODEA                   16
#define MODEB                   25
#define MODEC                   34
#define MODED                   0

/*
BIT		7	6	5	4	3	2	1	0	
TEC		F4	F3	F2	F1	C4	C3	C2	C1
*/

/*  Function Prototype Section
*
***************************************************/
void keyboard_init(void);
void keyboard_tec_matrix(void);

/****************************************************/

char keyboard_button_translate(char tecla);
void keyboard_set_mode(char new_mode);

#endif
