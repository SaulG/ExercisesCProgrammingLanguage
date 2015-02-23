#include <stdio.h>

int atoiF(char s[]);

int main() {
  char number [] = "19";
  printf("string %s - int %d\n", number, atoiF(number));
  return 0;
}

int atoiF(char s[]) {
  int i, n;
  n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    n = (10 * n) + (s[i] - '0');
  return n;
}
