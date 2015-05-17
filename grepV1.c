#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getLine(char *line, int max);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
    printf("Usage: find pattern\n");
  else
    while (getLine(line, MAXLINE) > 0)
      if (strstr(line, argv[1]) != NULL) {
	printf("%s", line); //pattern found
	found++;
      }
  return found;
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
