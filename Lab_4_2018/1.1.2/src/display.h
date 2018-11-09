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
#define	LDOUT			P6OUT	// dataport
#define LDIN			P6IN
#define	LDSEL			P6SEL
#define	LDDIR			P6DIR

// defines for control
#define LCOUT			P3OUT
#define	LCDIR			P3DIR
#define LCSEL			P3SEL
#define	LCD_RS			BIT2	// bit meaning: 1 = Data , 0 = Control
#define LCD_RW			BIT3	// bit meanings: 0 = Write, 1 = Read
#define	LCD_E			BIT4	// Enable

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

void display_test_Write_CGRAM_MS(void);

#endif
