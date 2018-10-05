int f1(int *x, int *y, int n)
{
  int i, res;

  for(i = 0, res = 0; i < n; i++, x++, y++)  
    res += (*x) - 2*(*y);

  return res;
}

int main(void)
{
  int x[] = { -1, 0, 1, 2, 3};
  int y[] = { 5, 6, 7, 8, 9, 0x10};
  int n = 5;
  int suma;

  suma = f1(x,y,n);
  return(suma);
}
