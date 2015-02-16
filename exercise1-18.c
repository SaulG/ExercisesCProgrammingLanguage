#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int lim);
void cleanTabWhiteSpacesBlankLines(char to[], char from[]);

main() {
  int len;
  char line[MAXLINE];
  char aux[MAXLINE];
  while ( (len = getLine(line, MAXLINE)) != 0 ) {
    cleanTabWhiteSpacesBlankLines(aux, line);
    printf("Line cleaned: [%s]\n", aux);
  }
  return 0;
}

int getLine(char s[], int lim) {
  int i, c;
  i = 0;
  for(i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }  
  s[i] = '\0';
  return i;
}

void cleanTabWhiteSpacesBlankLines(char to[], char from[]) {
  int i;
  i = 0;
  while(from[i] != '\0') {
    if (!(from[i] == '\t' ||
	from[i] == ' ' ||
	from[i] == '\n'))      
      to[i] = from[i];
    ++i;
  }
}


