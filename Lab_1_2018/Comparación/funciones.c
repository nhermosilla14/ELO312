#include <stdio.h>
#include "funciones.h"

int multiply_pow_2_v1 (unsigned int number, unsigned int power)
{
  return number << power;
}

int multiply_pow_2_v2 (unsigned int number, unsigned int power)
{
  int result = 0;
  int count;
  int pow_of_2 = 1;
  for (count = 0; count < power; count++){
    pow_of_2 += pow_of_2;
  } 
  for (count = 0; count < pow_of_2 ; count++){
    result += number;
  }
  return result;
}

void comparar (int number, int power)
{
  int resultado_v1;
  int resultado_v2; 
  resultado_v1 = multiply_pow_2_v1 (number, power);
  printf("El resultado al calcular con multiply_pow_2_v1 es: %d\n",resultado_v1);
  resultado_v2 = multiply_pow_2_v2 (number, power);
  printf("El resultado al calcular con multiply_pow_2_v2 es: %d\n", resultado_v2);
}