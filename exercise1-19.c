#include <stdio.h>
#define MAXLINE 1000

void reverse(char line[]);
int getLine(char line[], int lim);

int main() {
  int len;
  char line[MAXLINE];
  
  while ((len=getLine(line, MAXLINE)) > 0) {
    reverse(line);
    printf("Reversed line: [%s]\n", line);
    line[0] = '\0';
  }
  return 0;
}

int getLine(char line[], int lim) {
  int i, c;
 
  for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  line[i] = '\0';
  return i;  
}

void reverse(char s[]) {
  int i, j, max;
  i = j = max = 0;
  char aux[MAXLINE];
  while (s[i] != '\0') {
    aux[i] = s[i];
    ++i;
  }

  while (i != 0) {
    printf("%d - [%c] [%c]\n", i, s[j], aux[i-1]); 
    s[j] = aux[i-1];
    --i;
    ++j;
  }
  s[j] = '\0';
  ++j;
}
