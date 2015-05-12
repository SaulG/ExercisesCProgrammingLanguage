#include <stdio.h>
#include <string.h>
#include "addressing.c"

#define MAXLINES 5000    /* max lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

int readlines_1(char *lineptr[], int nlines);
int readlines_2(char lineptr[][MAXLEN], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main() 
{
  int nlines; /* number of input lines read */
  char lineptr[MAXLINES][MAXLEN];
  if ((nlines = readlines_2(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}



int getLine(char *, int);
char *alloc(int);

/* readlines_1: read input lines */
int readlines_1(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getLine(line, MAXLEN)) > 0) 
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len-1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}


/* readlines_2: read input lines */
int readlines_2(char lineptr[][MAXLEN], int maxlines)
{
  int len, nlines;

  nlines = 0;
  while ((len = getLine(lineptr[nlines], MAXLEN)) > 0) 
    if (nlines >= maxlines)
      return -1;
    else
      lineptr[nlines++][len] = '\0';
  return nlines;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

/* getline: get line into s, return length */
int getLine(char *s, int lim) {
  int c, i;  
  char *line = s;
  i = 0;
  for (;lim > 0 && (c = getchar()) != EOF && c != '\n'; lim--, i++)
    *line++ = c;
  if (c == '\n')
    *line++ = c;
  *line = '\0';
  return i;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) 
{
  int i, last;
  void swap(char *v[], int i, int j);
  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++) {
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  }
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char v[], int i, int j)
{
  char *temp;  
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
