#include<stdio.h>
#define LIMIT_INPUT 10
#define LIMIT_OUTPUT 10000
#define MAX_STACK 10

void expand(char s1[], char s2[]);
int getLine(char line[], int limit);


/**
   void expand function:
   Expands shorthand notations like a-z in the string s1 into
   the equivalent complete list abc..xyz in s2. Also works for
   letters of either case and digits and handle cases like a-b-c
   and a-z0-9 and -a-z.
 **/
void expand(char s1[], char s2[]) {
  int iteraciones[MAX_STACK];
  int j = 0;
  for (int i = 0; ((s1[i] == '-') || (s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= '0' && s1[i] <= '9')) && (s1[i] != '\0') ; i ++) {    
    if (s1[i] != '-')
      iteraciones[j++] = s1[i];     
  }  
  iteraciones[j] = '\0';
  int s2_index = 0;
  for (int i = 0 ; iteraciones[i] != '\0' ; i++) {
    if (((iteraciones[i] >= '0' &&
	iteraciones[i] <= '9')  &&
	(iteraciones[i+1] >= '0' &&
	 iteraciones[i+1] <= '9')) ||
	((iteraciones[i] >= 'a' && 
	iteraciones[i] <= 'z') &&
	(iteraciones[i+1] >= 'a' && 
	 iteraciones[i+1] <= 'z'))) {
      for(int x = iteraciones[i]; x <= iteraciones[i+1]; x++)
	s2[s2_index++] = x; 
    } 
  }
  s2[s2_index] = '\0';
}

int main() {
  char shortNot[LIMIT_INPUT];
  char largeNot[LIMIT_INPUT];
  if (getLine(shortNot, LIMIT_INPUT) > 2) {
    expand(shortNot, largeNot);
    printf("shortNot:%s\nlargeNot:%s\n", shortNot, largeNot);
  } else {
    printf("Nothing to do here.\n");
  }
  return 1;
}


int getLine(char line[], int limit) {
  int i, c;
  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  if (c == '\n') 
    line[i++] = c;
  line[i] = '\0';
  return i;
}

