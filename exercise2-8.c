#include<stdio.h>
#include<math.h>

unsigned rightrot(unsigned x, int p, int n);
unsigned invertBinary(unsigned x);
double log2(double n);
int getBitsSize(double n);

int main() {
  int x = 45;
  int p = 4;
  int n = 2;
  printf("rightrot(%d, %d, %d) -> %d\n", x, p, n, rightrot(x, p, n));
  return 1;
}

unsigned rightrot(unsigned x, int p, int n) {
  unsigned aux = 0;
  int bitSize = getBitsSize(x);
  int init = (p + 1) - n;
  for (int i = init; i <= p; i++) {
    aux |= 1 & (x >> (p - i));
    aux = aux << 1;
  }
  aux = aux << init;
  if (bitSize > (p + 1))
    return (((1 << init) - 1) & x) | aux | ((((1 << ((p + 1) - bitSize)) - 1) << (p + 1)) & x);
  else
    return (((1 << init) - 1) & x) | aux;
}

unsigned invertBinary(unsigned x) {
  unsigned aux = 0;
  int bitSize = getBitsSize(x) - 1;
  for (int i = 0; i <= bitSize; i++) {
    aux |= 1 & x >> i;
    if (bitSize != i)
      aux = aux << 1;
  }
  return aux;
}


int getBitsSize(double n) {
  return (int)ceil(log2(n));
}

double log2(double n) {
  return log(n) / log(2);
}
