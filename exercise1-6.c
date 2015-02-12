#include <stdio.h>

main () {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(c);
    printf ("VALOR DE GETCHAR() != EOF = %d\n", (c != EOF));
  }
  printf ("VALOR DE GETCHAR() != EOF = %d\n", (c != EOF));
}
