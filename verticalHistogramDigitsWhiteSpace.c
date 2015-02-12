#include <stdio.h>

#define IN 0
#define OUT 1
#define LIMITE 50

int main () {
  int flag, c, state, counter, words[LIMITE], aux[LIMITE];
  
  state = OUT;
  counter = flag = 0;
  
  for (int i = 0; i <= LIMITE; i++) {
    words[i] = 0;
  }

  while ((c = getchar()) != EOF) {
    if (c == '\n' || 
	c == '\t' || 
	c == ' ') {
      state = OUT;
      ++words[counter];
      counter = 0;
    } else {
      state = IN;
      ++counter;
    }    
  }
  
  printf("\n\n\n");  
  
  printf("**** Horizontal Histogram ****\n\n");    
  int mayor = 0;
  for (int i = 0; i <= LIMITE; i++) {
    if (words[i] == 0)
      continue;
    printf("Length: %d\t", i);
    if (words[i] > mayor) {
      mayor = words[i];
    }
    for(int j = 0; j < words[i]; j++)
      printf("@");
    printf("\n");    
  }

  printf("\n\n\n");  
  printf("**** Vertical Histogram ****\n\n");    

  while (mayor > 0) {
    for (int i = 0; i <= LIMITE; i++) {
      if (words[i] == 0) {
	continue;
      }
      if (words[i] >= mayor) {
	printf("#\t");
      } else {
	printf(" \t");
      }
    }
    printf("\n");    
    mayor--;
  }

  for (int i = 0; i <= LIMITE; i++) {
      if (words[i] == 0) {
	continue;
      }
      printf("%d\t", i);
  }
  printf("\n\n");    


}
