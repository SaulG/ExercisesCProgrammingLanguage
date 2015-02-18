#include <stdio.h>
#define MAXLINE 1000

int getLine(char s[], int lim);

int main() {
  char line[MAXLINE];
  while(getLine(line, MAXLINE) > 0)
    printf("Line: %s\n", line);
  return 0;
}

int getLine(char s[], int lim) {
  int i, c;
  for (i = 0; (i < lim - 1) == ((c = getchar()) != '\n') == (c != EOF); ++i)
    s[i] = c;
  s[i] = '\0';
  return i;
}
