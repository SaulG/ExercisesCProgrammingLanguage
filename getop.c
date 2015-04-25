#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getch(void);
void ungetch(int);

/*getop: get next operator or numeric operand */
/* Exercise 4-11. Modify getop so that it doesn't need to use ungetch.*/
int getop(char s[]) {
  int i, c;
  static int last_known = '\0';
  if (last_known != '\0') {
    c = last_known;
    last_known = '\0';
  } else
      c = getch();
  while ((s[0] = c) == ' ' || c == '\t')
    c = getch();
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-' && c != '+')
    return c; /* not a number */
  i = 0;
  if (c == '-' || c == '+') {
    if (!isdigit(c = getch())) {
      last_known = c;
      return s[i];
    } else
      s[++i] = c;
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()));
  if (c == '.')   /* collect fraction part */
    while (isdigit(s[++i] = c = getch()));
  s[i] = '\0';
  if (c != EOF)
    last_known = c;
  return NUMBER;
}
