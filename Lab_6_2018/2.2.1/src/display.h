#ifndef DISPLAY__H
#define DISPLAY__H
/*  Include section
*
***************************************************/
#include "msp430_version.h"

/*  Defines section
*
***************************************************/
// defines display layout
#define LCD_LINES			2
#define LCD_WIDTH			16

// defines for data
#define	LDOUT			P4OUT	// dataport
#define LDIN			P4IN
#define	LDSEL			P4SEL
#define	LDDIR			P4DIR

// defines for control
#define LCOUT			P1OUT
#define	LCDIR			P1DIR
#define LCSEL			P1SEL
#define	LCD_RS			BIT7	// bit meaning: 1 = Data , 0 = Control
#define LCD_RW			BIT6	// bit meanings: 0 = Write, 1 = Read
#define	LCD_E			BIT5	// Enable

/*  Function Prototype Section
*
***************************************************/

void display_clear(void);
void display_right_shift(void);
void display_left_shift(void);
void display_new_character(int, char*);
unsigned char display_get_pos(void);
void display_init(void);
void display_set_pos(unsigned char);
void display_lcd_clear(int, int);
int putchar(int c);
void display_test_Write_CGRAM_MS(void);
void display_add_new_character_CGRAM(int pos, char *new_char);

#endif
