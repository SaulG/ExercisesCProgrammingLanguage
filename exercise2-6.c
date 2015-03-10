#include<stdio.h>

unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main () {
  printf("getbits: %d\n", getbits(6, 2, 2));
  printf("setbits: %d\n", setbits(44, 4, 3, 47));
  return 1;
}

// 32 16 8 4 2 1
// 1   1 0 0 0 1 -> 49 getbits(49, 5, 3); 
// 0   0 0 1 1 0 -> 6  getbits(6, 2, 2);
// 0   0 0 0 1 1  -> 3 
unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p+1-n)) & ~(~0 << n);
}

// position #
// ------------------
//| 5  4  3  2  1  0 | p = 4
// ------------------ 
//| 32 16 8  4  2  1 |
// ------------------
//  0  1  0  0  1  0 -> 18 = x
//    |      |
//    |______|
//      n = 3
//
//  1  0  1  1  0  1 -> 45 = y
//          |     |
//          |_____|
//           n = 3
//
//     0 0 0 1 0 1 << 3 - 4 + 1
//
//     1 1 0 1 1 0
//    
//     1 0 0 1 1 0    1 0 1 0 1 1
// |   0 1 0 1 0 0    1 0 0 1 1 0
//     -----------    -----------
//     1 1 0 1 1 0    0 0 1 1 0 1
//
//     0 1 1 1 0 0     
//     0 0 0 0 0 1
//     -----------
//     0 1 1 1 0 1
unsigned setbits(unsigned x, int p, int n, unsigned y) {
  unsigned int mascara = (2 << (n - 1)) - 1;
  unsigned int and = mascara & y;
  printf("x = %d \t y = %d\t p = %d \t n = %d\n", x, y, p, n);
  printf("mascara = %d\n", mascara);
  printf("mascara AND y -> %d\n", and);
  unsigned int shift_left = and << ((p - n) + 1); 
  printf("%d << %d -> %d\n" , and, (p -n) + 1, shift_left);

  return (shift_left | x);
}
