#include<stdio.h>

main () {
  int c;

  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      while ((c = getchar()) == ' ') 
	;
      printf(" ");
    }
    putchar(c);
  }
  
}
