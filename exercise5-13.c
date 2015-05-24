#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PRINT_LINES 10    /* default lines to show */
#define MAXLINES 5000    /* max lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

int readLines(char (*text)[MAXLINES][MAXLEN], int maxlines);
int getLine(char (*text)[MAXLINES][MAXLEN], int lim, int nlines);
void writeLines(char (*text)[MAXLINES][MAXLEN], int nlines, int linesToPrint);

int main(int argc, char *argv[]) 
{
  //default settings
  int linesToPrint = DEFAULT_PRINT_LINES;
  int c;
  int index = 0;

  while (--argc > 0 && (*++argv)[index++] == '-') {
    c = (*argv)[index++];
    switch (c) {
    case 'n':
      if (isdigit((*argv)[++index])) {
	char valor[12];
	int index_valor = 0;      
	while (isdigit((*argv)[index]))
	  valor[index_valor++] = (*argv)[index++];
	valor[index_valor] = '\0';      
	linesToPrint = atoi(valor);
      }      
      break;
    default:
      printf("tail: illegal option %c\n", c);	
      argc = 0;
      return -1;
      break;
      
    }
  }
  int nlines; /* number of input lines read */
  char text[MAXLINES][MAXLEN];
  if ((nlines = readLines(&text, MAXLINES)) >= 0) {
    writeLines(&text, nlines, linesToPrint);
    return 0;
  } else {
    printf("error: input too big\n");
    return 1;
  }
}

/* readlines: read input lines */
int readLines(char (*text)[MAXLINES][MAXLEN], int maxlines)
{
  int len = 0, nlines = 0;
  while ((len = getLine(text, MAXLINES, nlines)) > 0){
    if (nlines >= maxlines)
      return -1;
    nlines++;
  }
  return nlines;
}


/* writelines: write output lines */
void writeLines(char (*text)[MAXLINES][MAXLEN], int nlines, int linesToPrint)
{
  int lim_lines = linesToPrint >= nlines? nlines - DEFAULT_PRINT_LINES : nlines - linesToPrint;
  while (((*text)[lim_lines]) && (lim_lines <= nlines)) {
    printf("%s", (*text)[lim_lines++]);
  }
}

/* getline: get line into s, return length */
int getLine(char (*text)[MAXLINES][MAXLEN], int lim, int nlines) {
  int c, i = 0;
  for (;lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--, i++) {
    (*text)[nlines][i] = c;
  }
  if (c == '\n')
    (*text)[nlines][i++]= c;
  (*text)[nlines][i] = '\0';
  return i;
}
