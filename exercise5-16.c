#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000 /* max lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES]; /* pointer to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *lineptr[], int left, int right,
	    int (*comp)(const char *, const char *));
int numcmp(const char *, const char *);
int strcmp_fold(const char *, const char *);
int getLine(char *, int);
char *alloc(int);

extern int numeric = 0; /* 1 if numeric sort */
extern int reverse = 0; /* 1 if reverse order */
extern int fold = 0; /* 1 if fold upper and lower case together */
extern int directory_order = 0; /* 1 if makes comparisons only on letters, numbers and blanks */

int strcmp_fd(const char *s1, const char *s2) 
{  
  char s1_u = fold? toupper(*s1) : *s1;
  char s2_u = fold? toupper(*s2) : *s2;
  if (directory_order && (!(isalnum(*s1) || isspace(*s1)) && !(isalnum(*s2) || isspace(*s2))))
    return 0;
  return strcmp(&s1_u, &s2_u);
}


/* sort input lines */
int main (int argc, char *argv[])
{
  int nlines; /* number of input lines read */
  
  while(argc-- > 0 && *argv != NULL) {
    if (strcmp(*argv, "-n") == 0) {
      numeric = 1;
    } else if (strcmp(*argv, "-r") == 0) {
      reverse = 1;
    } else if (strcmp(*argv, "-f") == 0) {
      fold = 1;
    } else if (strcmp(*argv, "-d") == 0) {
      directory_order = 1;
    } else if (strcmp(*argv, "-df") == 0) {
      directory_order = 1;
      fold = 1;
    }
    *argv++;
  }
  
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort1((void **) lineptr, 0, nlines-1, (int (*)(const char *, const char *))(numeric ? numcmp : strcmp_fd));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getLine(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = alloc(len)) == NULL) {
      return -1;
    } else {
      line[len-1] = '\0'; /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

#define ALLOCSIZE 2000000

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;    /* next free position */

char *alloc(int n) 
{
  if(allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
    allocp += n;
    return allocp - n;           /* old p */
  } else {                 /* not enough room */
    return 0;
  }
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


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  while(nlines-- > 0)
   printf("%s\n", *lineptr++);
  return;
}

/* qsort1: sort v[left]...v[right] into increasing order */
void qsort1(void *v[], int left, int right, int (*comp)(const char *, const char *))
{
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++) {
    if (reverse) {
      if ((*comp)(v[i], v[left]) > 0)
	swap(v, ++last, i);
    } else {
      if ((*comp)(v[i], v[left]) < 0)
	swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort1(v, left, last-1, comp);
  qsort1(v, last+1, right, comp);
}

/* numcmp: compare s1 nd s2 numerically */
int numcmp(const char *s1, const char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;
  
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

