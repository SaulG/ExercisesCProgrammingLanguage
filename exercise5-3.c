#include <stdio.h>
#include "strlen.c"
#define MAXSIZE 100

void strcatPointer(char *s, char *t);
void strcatArray(char s[], char t[]);

int main(){
  char s[MAXSIZE] = "testing the function strcat";
  char *t = "append this text";
  printf("before strcat: %s\n", s);
  strcatPointer(s, t);
  printf("after strcat: %s\n", s);
  return 1;
}

/* pointer version of strcat: concatenate t to end of s */
void strcatPointer(char *s, char *t)
{
  if ((strlen(t) + strlen(s)) >= MAXSIZE) {
    printf("it cannot be concatenated t is too big.");
  } else {
    while (*s++);
    *s--;
    while (*s++ = *t++)
      ;
  }
}


/* array version of strcat: concatenate t to end of s; s must be big enough */
void strcatArray(char s[], char t[])
{
  int i, j;
  
  i = j = 0;
  while (s[i] != '\0')   /* find end of s */
    i++;
  while ((s[i++] = t[j++]) != '\0') /* copy t */
    ;
}
