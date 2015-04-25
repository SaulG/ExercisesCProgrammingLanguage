#include <stdio.h>

int bufp = EOF;      /* index of the buffer */
int getch (void) /* get a (possibly pushed back) character */
{  
  int temp;
  if (bufp != EOF) {
    temp = bufp;
    bufp = EOF;
    return temp;
  }
  return getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp != EOF)
    printf("ungetch: too many characters\n");
  else if (c != EOF)
    bufp = c;
}
