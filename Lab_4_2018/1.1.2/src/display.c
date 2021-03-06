/***************************************************
* Nombre del modulo: display.c
*
* Modulo creado para la asignatura Elo312
* Laboratorio de Estructura de Computadores
* del departamento de Electr�nica de la Universidad
* T�cnica Federico Santa Mar�a. El uso o copia
* est� permitido y se agracede mantener el nombre
* de los creadores.
*
* Escrito inicialmente el 01/01/2004 Por Michael Kusch & Wolfgang Freund
* Modificado el 19/09/2014           Por Mauricio Sol�s.
*
* Descripci�n del m�dulo:
* Modulo driver display
* Contiene las funciones que permiten manejar un display
* LCD.
***************************************************/

/*  Include section
*
***************************************************/
#include "display.h"

/*  Defines section
*
***************************************************/
#define LCD_PORT_INIT   {LDSEL = 0x0; LCDIR |= (LCD_RS + LCD_RW + LCD_E); LCSEL &= ~(LCD_RS + LCD_RW + LCD_E);}
#define LCD_READ(x)     {SET_BIT(LCD_E); LCD_PDELAY; (x) = LDIN; RST_BIT(LCD_E); LCD_PDELAY;}
#define LCD_WRITE(x)    {LDDIR = 0xff; LDOUT = x; LCD_ENABLE(); LDDIR = 0;}

#define LCD_PDELAY      {asm("NOP"); asm("NOP"); asm("NOP"); asm("NOP");}

#define SET_BIT(x)      (LCOUT |= (x))
#define RST_BIT(x)      (LCOUT &= ~(x))

#define LCD_ENABLE()    {SET_BIT(LCD_E); LCD_PDELAY; RST_BIT(LCD_E);}
#define LCD_WAIT()      udelay(120)


/*  Local Function Prototype Section
*
***************************************************/
void udelay(unsigned int);
unsigned char display_wait_BF(void);
char display_get_data(void);
unsigned char display_lcd_addr(int);
void display_send_cmd(unsigned char);
void display_send_data(char);
int putchar(int c);
int display_lcd_line(unsigned char);
int display_lcd_copy(unsigned char, unsigned char, int);
void display_lcd_scroll_up(void);
void display_add_new_character_CGRAM(int pos, char *new_char);
/*  Global Variables Section
*
***************************************************/


////////////////////////////////////////
//        RUTINA A CALIBRAR           //
//                                    //
/**************************************************
* Nombre    		: void udelay(unsigned int arg1)
* returns			: void
* arg1				: Cantidad de microsegundos
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Hace un retardo de arg1
* microsegundos
**************************************************/
void udelay(unsigned int x)
{
	unsigned int i;
	for (i = 0; i < x; i++)
	{
		LCD_PDELAY;
		LCD_PDELAY;
	}
}
//                                    //
////////////////////////////////////////


////////////////////////////////////////
//     RUTINAS NO IMPLEMENTADAS       //
//                                    //


/**************************************************
* Nombre    		: unsigned char display_wait_BF(void)
* returns			: Direcci�n actual del cursor
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Espera a que el display est� listo
* para recibir nuevos comandos o datos
**************************************************/
#pragma inline = forced
unsigned char display_wait_BF(void)
{
	unsigned char add;
        unsigned char db;
        do {
          SET_BIT(LCD_RW);
          RST_BIT(LCD_RS);
          LCD_READ(db);
          add = db & 0x7F;
        } while ( db & 0x80);
	/*udelay(120); // solucion parche!! */

	return add;
}


/**************************************************
* Nombre    		: void display_clear(void)
* returns			: void
* Creada por		: Mauricio Sol�s
* Fecha creaci�n	: 19/09/2014
* Descripci�n		: Limpia el contenido del display
**************************************************/
void display_clear(void)
{
	RST_BIT(LCD_RS + LCD_RW);
        LCD_WRITE(0x01);
        display_wait_BF();

}


/**************************************************
* Nombre    		: void display_right_shift(void)
* returns			: void
* Creada por		: Mauricio Sol�s
* Fecha creaci�n	: 19/09/2014
* Descripci�n		: Corre el "visor" del display en un
* caracter hacia la derecha
**************************************************/
void display_right_shift(void)
{
	RST_BIT(LCD_RS + LCD_RW);
        LCD_WRITE(0x1C);
        display_wait_BF();
}


/**************************************************
* Nombre    		: void display_left_shift(void)
* returns			: void
* Creada por		: Mauricio Sol�s
* Fecha creaci�n	: 19/09/2014
* Descripci�n		: Corre el "visor" del display en un
* caracter hacia la izquierda
**************************************************/
void display_left_shift(void)
{
	RST_BIT(LCD_RS + LCD_RW);
        LCD_WRITE(0x18);
        display_wait_BF();
}

/**************************************************
* Nombre    		: void display_new_character(int arg1, char* arg2)
* returns			: void
* arg1				: Direcci�n del display donde se debe empezar a escribir
* arg2				: Puntero al arreglo que contiene el nuevo caracter a escribir
* Creada por		: Mauricio Sol�s
* Fecha creaci�n	: 19/09/2014
* Descripci�n		: Escribe en el display un nuevo caracter arg2, en la direcci�n
* arg1
**************************************************/
void display_new_character(int pos, char* data)
{
	LCD_WRITE(0x80 + (pos & 0x7F));
        display_wait_BF();
        SET_BIT(LCD_RS);
        RST_BIT(LCD_RW);
        LCD_WRITE(*data);
        display_wait_BF();
}

///////////////////////////////////////
//Rutinas Implementadas


/**************************************************
* Nombre    		: unsigned char display_get_pos(void)
* returns			: Direcci�n actual del cursor
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Retorna la posici�n actual del cursor
**************************************************/
unsigned char display_get_pos(void)
{
	unsigned char val;
        display_wait_BF();
	SET_BIT(LCD_RW);
	RST_BIT(LCD_RS);
	LCD_READ(val);
	return val&0x7F;
}

/**************************************************
* Nombre    		: char display_get_data(void)
* returns			: Caracter sobre el que est� el cursor del display
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Env�a el comando para leer el caracter sobre
* el que est� el cursor del display y lo retorna
**************************************************/
char display_get_data(void)
{
	char value;
	display_wait_BF();
	SET_BIT(LCD_RS|LCD_RW);
	LCD_READ(value);
	RST_BIT(LCD_RS|LCD_RW);
	return value;
}

/**************************************************
* Nombre    		: void display_init(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Inicializa el display
**************************************************/
void display_init(void)
{
	udelay(15000);
	LCD_PORT_INIT;
	RST_BIT(LCD_RS + LCD_RW);

	LCD_WRITE(0x30);
	udelay(500);

	LCD_WRITE(0x30);
	udelay(120);

	LCD_WRITE(0x30);
	udelay(200);

	LCD_WRITE(0x38);
	udelay(200);
	LCD_WRITE(0x0F);

	udelay(200);
	LCD_WRITE(0x1);
	udelay(5000);
	LCD_WRITE(0x06);
	udelay(200);
}

/**************************************************
* Nombre    		: void display_set_pos(unsigned char arg1)
* returns			: void
* arg1				: Direcci�n a la que se debe enviar el cursor
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Setea la posici�n del cursor en el display
**************************************************/
void display_set_pos(unsigned char add)
{
	display_send_cmd(0x80 + add);
}


/**************************************************
* Nombre    		: unsigned char display_lcd_addr(int arg1)
* returns			: Direcci�n de la l�nea
* arg1				: N�mero de la l�nea
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Entrega la direcci�n de una determinada l�nea
* en el display.
* dado una l�nea (0, 1, etc) retorna la direcci�n de memoria
**************************************************/
unsigned char display_lcd_addr(int line)
{
	switch (LCD_LINES)
	{
	case 2:
		return (line > 0) ? 0x40 : 0x0;

	case 4:
		if (line == 0) return 0x0;
		else if (line == 1) return 0x40;
		else if (line == 2) return LCD_WIDTH;
		return (0x40 + LCD_WIDTH);

	default: return 0;
	}
}

/**************************************************
* Nombre    		: void display_send_cmd(unsigned char arg1)
* returns			: void
* arg1				: Comando a enviar
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Env�a un comando al display
**************************************************/
void display_send_cmd(unsigned char value)
{
	display_wait_BF();
	RST_BIT(LCD_RS + LCD_RW);
	LCD_WRITE(value);
}

/**************************************************
* Nombre    		: void display_send_data(char arg1)
* returns			: void
* arg1				: Data a enviar
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Env�a un dato al display
**************************************************/
void display_send_data(char value)
{
	display_wait_BF();
	SET_BIT(LCD_RS); RST_BIT(LCD_RW);
	LCD_WRITE(value);
}

/**************************************************
* Nombre    		: int putchar(int arg1)
* returns			: El caracter ingresado como argumento
* arg1				: El caracter.
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Maneja los caracteres que "env�a"
* la funci�n printf de la biblioteca stdio
**************************************************/
int putchar(int c)
{
	int line;
        unsigned char pos;
	if (c == '\n'){
                pos = display_get_pos();
                line = display_lcd_line(pos);
                switch (line){
                case 0:
                    display_set_pos(0x40);
                    break;
                case 1:
                    display_set_pos(0);
                    display_lcd_scroll_up();
                    //display_set_pos(0x40);
                    break;
                case -1:
                    if (pos < 0x40){
                        display_set_pos(0x40);
                        break;
                    } else {
                        display_lcd_scroll_up();
                        display_set_pos(0x40);
                        break;
                    }  
                }
                
                return c;
	}

	if (c == '\r'){
                display_set_pos(0);
		return c;
	}

	if (c == '\t'){
		pos = display_get_pos();
                line = display_lcd_line(pos);
                switch (line){
                case 0:
                    pos = (pos+1) % 4 ? 4*(pos+1/4) + 4 : pos + 1;
                    break;
                case 1:
                    pos = (pos-0x40+1) % 4 ? 4*((pos-0x40+1)/4) + 3 + 0x40 +1 : pos + 1;
                    break;
                }
		display_set_pos(pos);
		return c;
	}
	if( c== '\b'){
		pos = display_get_pos();
		if (pos > 0)
                    display_set_pos(pos - 1);
                else if (pos == 0x40)
                    display_set_pos(0x0F);
                return c;
	}

	display_send_data((unsigned char) c);
	return c;
}

/**************************************************
* Nombre    		: int display_lcd_line(unsigned char addr)
* returns			: N�mero de la l�nea
* arg1				: Direcci�n del display
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Dada una direcci�n retorna el n�mero de l�nea
**************************************************/
int display_lcd_line(unsigned char addr)
{
	int line;

	for (line = 0; line < LCD_LINES; line++)
		if (addr >= display_lcd_addr(line) &&
			addr < display_lcd_addr(line) + LCD_WIDTH)
			return line;
	return -1;
}

/**************************************************
* Nombre    		: void display_lcd_clear(int arg1, int arg2)
* returns			: void
* arg1				: Direcci�n de inicio
* arg2				: Cantidad de caracteres
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Limpia - arg2 - caracteres desde arg1
**************************************************/
void display_lcd_clear(int from, int len)
{
	int i;

	display_set_pos(from);
	for (i = 0; i < len; i++)
		display_send_data(' ');
	display_set_pos(from);
}

/**************************************************
* Nombre    		: int display_lcd_copy(unsigned char arg1, unsigned char arg2, int arg3)
* returns			: 0 si se hizo, -1 si hay un error de direcciones.
* arg1				: Direcci�n de inicio
* arg2				: Direcci�n destino
* arg3				: Cantidad de caracteres
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Copia - arg3 - caracteres desde - arg1 - a - arg2 -
**************************************************/
int display_lcd_copy(unsigned char from, unsigned char to, int len)
{
	char data[LCD_WIDTH];
	int i;

	if ((len > LCD_WIDTH) || (from > (0x7f - len))
		|| (to > (0x7f - len))) return -1;

	display_set_pos(from);
	for (i = 0; i < len; i++)
		data[i] = display_get_data();
	display_set_pos(to);
	for (i = 0; i < len; i++)
		display_send_data(data[i]);
	return 0;
}

/**************************************************
* Nombre    		: void display_lcd_scroll_up(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creaci�n	: 01/01/2004
* Descripci�n		: Copia l�nea i en l�nea i - 1 para todo el display
**************************************************/
void display_lcd_scroll_up(void)
{
	int line;
	for (line = 0; line < LCD_LINES - 1; line++)
		display_lcd_copy(display_lcd_addr(line + 1), display_lcd_addr(line), LCD_WIDTH);
	display_lcd_clear(display_lcd_addr(line), LCD_WIDTH);
}
//                                    //
////////////////////////////////////////


/**************************************************
* Nombre    		: void display_test_Write_CGRAM_MS(void)
* returns			: void
* Creada por		: Mauricio Sol�s
* Fecha creaci�n	: 20/09/2014
* Descripci�n		: Escribe en la memoria CGRAM
* un caracter nuevo ... un robot.SET_BIT(LCD_RW);
	RST_BIT(LCD_RS);
**************************************************/
const char new_char0[]={BIT2,BIT3+BIT1,BIT2,BIT4+BIT3+BIT2+BIT1+BIT0,BIT2,BIT3+BIT1,BIT3+BIT1,BIT4+BIT3+BIT1+BIT0};

const char new_char1[]={0x0,0x0,0x0,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};

const char new_char2[]={0x0,0x0,0x0,BIT2,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};

const char new_char3[]={0x0,BIT2,0x0,BIT2,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};

const char new_char4[]={BIT2,0x0,BIT2,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};

const char new_char5[]={0x0,BIT2,0x0,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};

const char new_char6[]={BIT2,0x0,0x0,0x0,0x0,BIT2,BIT3+BIT1,BIT4+BIT2+BIT0};

void display_test_Write_CGRAM_MS(void)
{
	int i=0;
	int x=1;
	display_send_cmd(0x40+(x<<3));//set CG RAM Address
	for(i=0; i<8; i++)
	{
		display_send_data(new_char0[i]);
	}
}

/**************************************************
* Nombre    		: void display_add_new_character_CGRAM(int pos, char *new_char)
* returns		: void
* arg1			: Posici�n del caracter nuevo
* arg2                  : Caracter nuevo a escribir en la CGRAM
* Creada por		: Nicol�s Hermosilla
* Fecha creaci�n	: 15/11/2018
* Descripci�n		: Escribe un nuevo caracter en la CGRAM,
                          en la direcci�n dada en address.
**************************************************/

void display_add_new_character_CGRAM(int pos, char *new_char)
{
	int i=0;
	display_send_cmd(0x40+(pos<<3));//set CG RAM Address
	for(i=0; i<8; i++)
	{
		display_send_data(new_char[i]);
	}
}
