#include <ctype.h>
#include "getch.c"

int getint(int *pn);

int main() {
  int pn;
  getint(&pn);
  printf("%d\n",pn);
  return 1;
}

/* getint: get next integer from input into *pn */
int getint(int *pn){
  int c, sign;
  
  while (isspace(c = getch())) /* skip white space */
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-')? -1 : 1;
  if (c == '+' || c == '-') {
    if (!isdigit(c = getch())) {
	ungetch(c);
	*pn = -1;
	return 0;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}
