#include <stdio.h>
#include "strlen.c"

int strend(char *s, char *t);

int main() {
  char *s = "testing the function strend";
  char *t = "strend";
  printf("strend -- s: %s t: %s return: %d\n", s, t, strend(s, t));
  t = "lol";
  printf("strend -- s: %s t: %s return: %d\n", s, t, strend(s, t));

  return 1;
}


/* strend: return 1 if the string t occurs at the end of the string s, and zero otherwise */
int strend(char *s, char *t) 
{
  if (strlen(t) <= strlen(s)) {
    while (*s++);
    *s - strlen(t);
    while (*s++ == *t++)
    return (*t)? 1 : 0;
  } else
    return 0;
}
