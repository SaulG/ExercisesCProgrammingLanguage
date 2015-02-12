#include<stdio.h>

#define MAX_CHAR 1000

main () {
  int c, freq[MAX_CHAR];
  
  for(int i = 0; i <= MAX_CHAR; i++)
    freq[i] = 0;
  
  while((c = getchar()) != EOF) {
    if (c != ' ' &&
	c != '\t' &&
	c != '\n')
      ++freq[c];
  }
  
  for(int i = 0; i <= MAX_CHAR; i++) {
    if (freq[i] == 0)
      continue;
    printf("Character: '%c'\t", (char)i);
    for(int j = 0; j < freq[i]; j++)
      printf("@");
    printf("\t total: %d", freq[i]);
    printf("\n");
  }
}
