#include<stdio.h>

/*
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x.
Explain why. Use this observation to write a faster version of bitcountV1.

The reason is that the rightmost 1-bit is one, and if you delete one from lets say 25, where 25 its
equal to 11001, then you apply minus one, it'll be equal to 11000, and if you apply & of minus the original
value it'll be equal to 11001 & 11000, logically it'll be 11000. It can be applied to the current bitcountV1
to improve the operation by deleting the if statement and modifying the for. The thing that changes in the 
for its the way to move by bits, instead of that, it'll be applied a logical operation using & with the current
value and the value minus one, until the current value is different to zero.

*/

int bitcountV2(unsigned x);
int bitcountV1(unsigned x);

int main() {
  printf("bitcount(%d) -> %d\n", 5, bitcountV2(5));
  return 0;
}

int bitcountV1(unsigned x) {
  int b;  
  for (b = 0; x != 0; x >>= 1)
    if (x & 01)
      b++;
  return b;
}

int bitcountV2(unsigned x) {
  int b;
  for (b = 0; x != 0; x &= (x-1))
    b++;
  return b;
}
