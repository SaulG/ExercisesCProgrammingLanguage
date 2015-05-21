#include <stdio.h>
#include <string.h>

#define MAXLINES 5000    /* max lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

int readLines(char *lineptr[MAXLEN], int nlines);
int getLine(char *s[], int);
void writeLines(char *lineptr[], int nlines);

int main() 
{
  int nlines; /* number of input lines read */
  char text[MAXLINES][MAXLEN];
  char (*lineptr)[MAXLEN] = &text;

  if ((nlines = readLines(&lineptr, MAXLINES)) >= 0) {
    writeLines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big\n");
    return 1;
  }
}

extern nlines = 0;
/* readlines: read input lines */
int readLines(char *lineptr[MAXLEN], int maxlines)
{
  int len, nlines;
  printf("readlines inicio\n");
  while ((len = getLine(&lineptr[0], MAXLEN)) > 0){
    printf("readline while %s\n", *lineptr);
    if (nlines >= maxlines)
      return -1;
    nlines++;
  }
  printf("readlines return\n");
  return nlines;
}


/* writelines: write output lines */
void writeLines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* getline: get line into s, return length */
int getLine(char *s[], int lim) {
  int c, i;  
  //char *line = &s;
  i = 0;
  printf("getLine inicio\n");
  for (;lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--, i++) {
    printf("getline for %c nlines: %d i: %d\n", c, nlines, i);
    s[nlines][i++] = c;
  }
  if (c == '\n')
    s[nlines][i++] = c;
  s[nlines][i] = '\0';
  printf("return getline %c\n", *s);
  printf("return getline %s\n", s);
  return i;
}
