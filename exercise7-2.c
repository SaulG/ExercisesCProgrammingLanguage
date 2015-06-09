#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OCTAL 'o'
#define HEXADECIMAL 'h'

#define OPTION_DEFAULT 0
#define OPTION_OCTAL 1
#define OPTION_HEXADECIMAL 2

#define MAXLINE 100
#define MAXLINES 1000

#define INDENT 20

int readLines(char *[MAXLINES], int);
int getLine(char *, int);
void writelines(char *[MAXLINES], int nlines);
void writelinesOctal(char *[MAXLINES], int nlines);
void writelinesHexadecimal(char *[MAXLINES], int nlines);

/* 
   exercise 7-2: Write a program that will print arbitrary input 
   a sensible way. As a minimum, it should print non-graphic 
   characters in octal or hexadecimal according to local custom, 
   and break long text lines. 
*/
int main(int argc, char **argv)
{  

  char lines[MAXLINES][MAXLINES];
  int option, nlines;
  while (argc-- > 1) {
    if (**++argv == '-') {
      switch(*++(*argv)) {
      case OCTAL:
	option = OPTION_OCTAL;
	break;
      case HEXADECIMAL:
	option = OPTION_HEXADECIMAL;
	break;
      default:
	option = OPTION_DEFAULT;
	break;
      }
    }
  }

  if ((nlines = readLines(lines, MAXLINES)) > 0) {
    switch(option) {
    case OPTION_OCTAL:
      writelinesOctal(lines, nlines);
      break;
    case OPTION_HEXADECIMAL:
      writelinesHexadecimal(lines, nlines);
      break;
    case OPTION_DEFAULT:
      writelines(lines, nlines);
      break;
    }
    return 0;
  } else {
    return 1;
  } 
}

/* writelines: write output lines */
void writelines(char *lineptr[MAXLINES], int nlines)
{
  int counter = 0;
  while (nlines-- > 0) {
    while(**lineptr != EOF && **lineptr != '\0') {
      printf("%c", *(*lineptr)++);
      counter++;
      if (INDENT < counter) {
	printf("\n");
	counter = 0;
      }
    }
    lineptr++;
    printf("\n");
    counter = 0;
  }
}

/* writelinesOctal: write output lines in octal*/
void writelinesOctal(char *lineptr[MAXLINES], int nlines)
{
  int counter = 0;
  while (nlines-- > 0) {
    while(**lineptr != EOF && **lineptr != '\0') {
      printf("%o", *(*lineptr)++);
      counter++;
      if (INDENT < counter) {
	printf("\n");
	counter = 0;
      }       
    }
    lineptr++;
    printf("\n");
    counter = 0;
  }
}

/* writelinesHexadecimal: write output lines in hexadecimal*/
void writelinesHexadecimal(char *lineptr[MAXLINES], int nlines)
{
  int counter = 0;
  while (nlines-- > 0) {
    while(**lineptr != EOF && **lineptr != '\0') {
      printf("%x", *(*lineptr)++);
      counter++;
      if (INDENT < counter) {
	printf("\n");
	counter = 0;
      }	
    }
    printf("\n");
    counter = 0;
  }
}


/* readLines: read input lines */
int readLines(char *linesptr[MAXLINES], int maxlines) {
  int len, nlines;
  char *p, line[MAXLINE];
  
  nlines = 0;
  while ((len = getLine(line, MAXLINE)) > 0)
    if (nlines >= maxlines || (p = (char *) malloc(len)) == NULL)
      return -1;
    else {
      strcpy(p, line);
      *linesptr++ = p;
      nlines++;
    }
  return nlines;
}

/* getLine: get the input line */
int getLine(char *s, int lim){
  int c, i;
  char *line = s;
  i = 0;
  for (;lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--, i++)
    *line++ = c;
  if (*line == '\n')
    *line++ = c;
  *line = '\0';
  return i;
}
