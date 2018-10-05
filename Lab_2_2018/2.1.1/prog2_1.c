#include<stdio.h>
int i1= 0, i2 = 1, i3 = 2;
int arr[5] = { 0, 1, 2, 3, 4};
char ch = 'o';

int brr[] = { 3, 2, 1, 0};
char *p1 = "hola";
char p2[]= " mundo";
long int li1 = 65534L;
long int li2 = -65534L;
double cte = 3/5;//¿Qué valor toma esta variable?

struct header{
    struct header *h;
    int  modo;
    float dato;
} cabecera = { &cabecera, 25, 3.0/5.0};//¿qué valor toma la variable dato?

int main(void)
{
    int j1, j2 = 0, j3;
	char *p3 = p2;
    j1 = i1 + i2 + i3 + j2;
    j2 = arr[0] + *(brr + 1) - j1;
    cabecera.modo = j1 + 3;
    cte += 1/2;
    cabecera.dato = cte - 0.1;
    *(p1 + 3) = ch;
    cte = cte + li1 + li2;
	j3 = sizeof(p2);
	j3 = sizeof(p3);
	*(p3+4)='B';
    return(j3);
}
