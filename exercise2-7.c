#include <stdio.h>


unsigned invert(int x, int p, int n);

int main() {
  int x = 0;
  int p = 0;
  int n = 1;
  printf("invert(%d, %d, %d) -> %d \n", x, p , n, invert(x, p, n));
  return 1;
}

unsigned invert(int x, int p, int n) {
  // 0 0 1 1 1 -> 1 1 0 0 0
  unsigned int mascara = (2 << (n - 1)) - 1;
  printf("mascara: %d \n", mascara << ((p - n) + 1));
  return (mascara << ((p - n) + 1)) ^ x;
}
