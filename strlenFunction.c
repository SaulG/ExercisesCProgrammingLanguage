#include <stdio.h>
#define MAXLINE 1000

int strLen(char s[]);
int getLine(char s[], int lim);

int main (){  
  char line[MAXLINE];
  while(getLine(line, MAXLINE) > 0)    
    printf("Length of char: %d\nLine: %s\n", strLen(line), line);
  return 0;
}

int getLine(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++)
    s[i] = c;
  s[i] = '\0';
  return i;
}

int strLen(char s[]) {
  int i;
  i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}
