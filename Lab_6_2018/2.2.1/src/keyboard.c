/***************************************************
* Nombre del modulo: keyboard.c
*
* Modulo creado para la asignatura Elo312
* Laboratorio de Estructura de Computadores
* del departamento de Electrónica de la Universidad
* Técnica Federico Santa María. El uso o copia
* está permitido y se agracede mantener el nombre 
* de los creadores.
*
* Escrito inicialmente el 01/01/2004 Por Michael Kusch & Wolfgang Freund
* Modificado el 24/09/2014           Por Mauricio Solís & Andrés Llico.
*
* Descripción del módulo:
* Modulo driver teclado matricial
* Contiene las funciones que permiten manejar el
* teclado matricial.
***************************************************/

/*  Include section
*
***************************************************/
#include "keyboard.h"
#include "display.h"
#include "uart.h"
/*  Defines section
*
***************************************************/
typedef unsigned char uchar;

/*  Local Function Prototype Section
*
***************************************************/
void keyboard_button_action(char);


/*  Global Variables Section
*
***************************************************/
uchar BUTMAT_CLK = 0;           // cuántas interrupciones se lleva presionado el botón
uchar BUTMAT_PREV = 0xFF;       // tecla de la lectura anterior, FF => ninguna.


////////////////////////////////////////
//       RUTINAS IMPLEMENTADAS        //
//                                    //

/**************************************************
* Nombre    		: void keyboard_init(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Inicializa los puertos del 
* driver del teclado.
**************************************************/
void keyboard_init(void)
{
    P2SEL = 0x00;
    PTOUT = 0x00;
    PTDIR = 0x00;
}

/**************************************************
* Nombre    		: void keyboard_tec_matrix(void)
* returns			: void
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Lee la matriz de botones y 
* llama a la función keyboard_button_action() cuando
* detecta que se ha presionado una tecla (o se ha mantenido
* presionada una tecla).
* Esta función debe ser llamada cada cierta cantidad de tiempo.
**************************************************/
void keyboard_tec_matrix(void)
{
    uchar BUTMAT = 0xFF;        // tecla de 0 a 15
    uchar k, temp;

    temp = 0x00;
    for(PTDIR = 0x10; PTDIR > 0; PTDIR <<= 1) {
        asm("NOP"); asm("NOP");
        asm("NOP"); asm("NOP");
        asm("NOP");
        k = (((~PTIN) & 0x0F) | PTDIR);
        if ( (k & 0x0F) ){	           // si hay algún bit de columna en 0, entonces if es verdadero
            temp = k;	               // y se guarda el valor de la columna y filas activas
        }
    }

    if (temp) {	                       // hubo tecla presionada?
        switch	(temp & 0xF0) {
        case BIT4:
            BUTMAT = 0;	 // fila 1
            break;
        case BIT5:
            BUTMAT = 4;	 // fila 2
            break;
        case BIT6:
            BUTMAT = 8;	 // fila 3
            break;
        case BIT7:
            BUTMAT = 12; // fila 4
            break;
        }

        switch	(temp & 0x0F) {
        case BIT0:
            asm("NOP");
            BUTMAT += 0; // col 1
            break;
        case BIT1:
            BUTMAT += 1; // col 2
            break;
        case BIT2:
            BUTMAT += 2; // col 3
            break;
        case BIT3:
            BUTMAT += 3; // col 4
            break;
        }

        if (BUTMAT != BUTMAT_PREV) {              // botón presionado es distinto al anterior?
            BUTMAT_PREV = BUTMAT;
            BUTMAT_CLK = 0;
            keyboard_button_action(BUTMAT);
        }
        else {
            if (++BUTMAT_CLK == 100) {            // presionada por más de 100*10[ms] (1 [s])?
                keyboard_button_action(BUTMAT);   // actuar como si se volvió a presionar el botón
                BUTMAT_CLK -= 33;                 // por cada 0.5 [s] que siga presionado el botón
            }
        }
    }
    else
        BUTMAT_PREV = 0xFF;                       // ningún botón presionado
}
//                                    //
////////////////////////////////////////


char keyboard_mode = MODEA;


////////////////////////////////////////
//     RUTINAS NO IMPLEMENTADAS       //
//                                    //

/**************************************************
* Nombre    		: void keyboard_button_action(char arg1)
* returns			: void
* arg1				: Tecla presionada
* Creada por		: Michael Kusch
* Fecha creación	: 01/01/2004
* Descripción		: Realiza una accion segun la
tecla que ha sido presionada.
**************************************************/
void keyboard_button_action(char tecla)
{
  static char letra = '\0';
  char tecla_real = keyboard_button_translate(tecla);
  switch (tecla_real){
  case 'A':
    if (letra != 'A'){
     // letra = 'A';
      uart_0_send(65);
    }
    break;
  case 'B':
    if (letra != 'B'){
      uart_0_send(66);
     // letra = 'B';
    }
    break;
  case 'C':
    if (letra != 'C'){
      uart_0_send(67);
    //letra = 'C';
    }
    break;
  case 'D':
    if (letra != 'D'){
      uart_0_send(68);
    //  letra = 'D';
    }
    break;
  case '*':
    uart_0_send('\b');
    break;
  case '#':
    uart_0_send('\n');
    break;
  case '1':
    uart_0_send('0');
    break;
  case '2':
    uart_0_send('1');
    break;
  case '3':
    uart_0_send('2');
    break;
  case '4':
    uart_0_send('4');
    break;
  case '5':
    uart_0_send('5');
    break;
  case '6':
    uart_0_send('6');
    break;
  case '7':
    uart_0_send('8');
    break;
  case '8':
    uart_0_send('9');
    break;
  case '9':
    uart_0_send('1');
    uart_0_send('0');
    break;
  case '0':
    uart_0_send('1');
    uart_0_send('4');
    break;
  }
    letra = tecla_real;
}

/**************************************************
* Nombre    		: char keyboard_button_translate(char arg1)
* returns			: void
* arg1				: Tecla presionada
* Creada por		: Nicolás Hermosilla
* Fecha creación	: 30/11/2018
* Descripción		: Traduce el código recibido desde el teclado
a su valor ascii correspondiente.
**************************************************/

char keyboard_button_translate(char tecla)
{
  switch (tecla){
  case 0: //D
    return('D');  
    break;
  case 1: //C
    return('C'); 
    break;
  case 2: //B
    return('B'); 
    break;
  case 3: //A
    return('A'); 
    break;
  case 4:
    return('#'); 
    break;
  case 5:
    return('9'); 
    break;
  case 6:
    return('6'); 
    break;
  case 7:
    return('3'); 
    break;
  case 8:
    return('0'); 
    break;
  case 9:
    return('8'); 
    break;
  case 10:
    return('5'); 
    break;
  case 11:
    return('2'); 
    break;
  case 12:
    return('*'); 
    break;
  case 13:
    return('7'); 
    break;
  case 14:
    return('4'); 
    break;
  case 15:
    return('1'); 
    break;
  } 
}

/**************************************************
* Nombre    		: void keyboard_set_mode(enum mode new_mode)
* returns			: void
* arg1				: Tecla presionada
* Creada por		: Nicolás Hermosilla
* Fecha creación	: 30/11/2018
* Descripción		: Setea el modo de uso del teclado.
**************************************************/

void keyboard_set_mode(char new_mode){
  keyboard_mode = new_mode;
}

