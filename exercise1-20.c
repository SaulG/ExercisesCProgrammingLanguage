#include <stdio.h>
#define MAXLINE 1000
#define SPACE_TAB 4

int getLine(char s[], int lim);
void detab(char s[], int space);

int main() {
  char line[MAXLINE]; 
  while (getLine(line, MAXLINE) > 0) {
    detab(line, SPACE_TAB);
    printf("%s", line);
  }
  return 0;
}

void detab(char s[], int space) {
  int i = 0;
  int contador = 0;
  char aux[MAXLINE];

  while (s[i] != '\0') {
    if (s[i] == '\t') {
      for (int j = 0; j < space; j++) {
	aux[contador] = ' ';
	++contador;
      }
    } else {
      aux[contador] = s[i];
      ++contador;
    }
    ++i;
  }
  i = 0;
  while (aux[i] != '\0')  {
    s[i] = aux[i];
    ++i;
  }
}

int getLine(char s[], int lim) {
  int i, c;
  for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  s[i] = '\0';
  return i;
}
