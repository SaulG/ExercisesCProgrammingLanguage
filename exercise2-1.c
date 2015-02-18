#include <stdio.h>
#include <limits.h>

int main() {
  printf("Number of bits in a byte %d\n", CHAR_BIT);
  printf("Minimum value for signed char %d\n", SCHAR_MIN);
  printf("Maximum value for signed char %d\n", SCHAR_MAX);
  printf("Maximum value for an unsigned char %d\n", UCHAR_MAX);
  printf("Minimum value for char type %d\n", CHAR_MIN);
  printf("Maximum value for char type %d\n", CHAR_MIN);
  printf("Minimum value of short type %d\n", SHRT_MIN);
  printf("Maximum value of short type %d\n", SHRT_MAX);
  printf("Minimum value of an int type %d\n", INT_MIN);
  printf("Maximum value of an int type %d\n", INT_MAX);
  printf("Minimum value of long type %ld\n", LONG_MIN);
  printf("Maximum value of long type %ld\n", LONG_MAX);
  

  return 0;
}
