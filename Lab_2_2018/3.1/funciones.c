

int suma(int x1, int x2, int x3, int x4, int x5, int x6)
{
  return(x1 + x2 + x3 + x4 + x5 + x6);
}

int suma2(int *x1, int *x2, int *x3, int *x4, int *x5, int *x6)
{
  return(*x1 + *x2 + *x3 + *x4 + *x5 + *x6);
}

long int suma3(int x1, int x2, int x3, int x4, int x5, int x6)
{
  long int loquesea;
  loquesea = x1 + x2 + x3 + x4 + x5 + x6;
  return (loquesea);
}