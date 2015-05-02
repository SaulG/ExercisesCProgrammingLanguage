#include <ctype.h>
#include "getch.c"


int getfloat(double *pn);

int main() {
  double pn;
  getfloat(&pn);
  printf("%g\n",pn);
  return 1;
}

/* getfloat: get next float from input into *pn */
int getfloat(double *pn) {
  int c, sign;
  double power = 10.0;

  while (isspace(c = getch())) /* skip white space */
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }

  sign = (c == '-')? -1 : 1;
  if (c == '+' || c == '-' || c == '.') {
    if (!isdigit(c = getch())) {
      ungetch(c);
      *pn = -1;
      return 0;
    }
  }
  
  for (*pn = 0.0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  if (c == '.') {
    c = getch();
    for (; isdigit(c); c = getch()) {
      *pn = *pn + ((c - '0') / power);
      power *= 10.0;
    }
  }
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}
