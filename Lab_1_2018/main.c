#include <stdio.h>

unsigned int numbers[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
unsigned int number_to_find =21;

void search(int number_to_find, unsigned int numbers[])
{
  int localizado = 0; 
  int contador = 0;
  while (contador < 20){
    if (numbers[contador] == number_to_find){
      localizado = 1;
      break;
    } else {
      contador += 1;
    }
  }
  if (localizado == 0)
  //  printf("El valor no existe en el arreglo\n");
    asm("nop");
  else
  //  printf("El indice del arreglo es: %d", contador);
        asm("nop");

}

int main( void )
{
  search(number_to_find, numbers); 
  return 0;
}