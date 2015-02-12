#include <stdio.h>

#define IN 0
#define OUT 1
#define LIMITE 50

main () {
  int c, state, counter, words[LIMITE];
  
  state = OUT;
  counter  = 0;
  
  for (int i = 0; i <= LIMITE; i++)
    words[i] = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n' || 
	c == '\t' || 
	c == ' ') {
      state = OUT;
      counter = 0;
    } else {
      state = IN;
      ++counter;
      ++words[counter];
    }    
  }

  for (int i = 0; i <= LIMITE; i++) {
    if (words[i] == 0)
      continue;
    printf("Length: %d\t", i);
    for(int j = 0; j < words[i]; j++)
      printf("|");
    printf("\n");    
  }

}
