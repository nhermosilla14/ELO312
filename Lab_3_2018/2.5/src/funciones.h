#ifndef FUNCIONES_H
#define FUNCIONES_H

/*
 * void toggle_port (void)
 *
 * Cambia el estado (salida) de todos los pines de P2
 *
 */

void toggle_port(void);

/*
 * void shift_port (void)
 *
 * Hace un corrimiento a la derecha a los pines de P2 hasta que LSB sea 1.
 * Después el corrimiento lo hace a la izquierda, hasta que el MSB sea 1, etc.
 *
 */

void shift_port(void);

#endif