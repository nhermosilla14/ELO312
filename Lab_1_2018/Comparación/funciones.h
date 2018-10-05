#ifndef func
#define func 

/* Retorna 2^power * number
*
*/
unsigned int multiply_pow_2_v1 (unsigned int number, unsigned int power);


/* Retorna 2^power * number calculado según la definición
*
*/
unsigned int multiply_pow_2_v2 (unsigned int number, unsigned int power);

/* Imprime en pantalla el resultado del llamado a cada una de las funciones
*  anteriores.
*/
void comparar (unsigned int number, unsigned int power);
#endif