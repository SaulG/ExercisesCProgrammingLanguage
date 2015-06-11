#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(double*);
void push(double);
double pop(void);
int getch (void);

/* reverse Polish calculator */
int main () {
  int type;
  double op2;
  
  while ((type = getop(&op2)) != EOF) {
    switch (type) {
    case NUMBER:      
      push(op2);
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
	push(pop() / op2);
      else
	printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
	push((int)pop() % (int)op2);
      else 
	printf("error: zero divisor\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %c \n", type);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100    /* maximum depth of val stack */
int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

#include <ctype.h>
void ungetch(int);
/*getop: get next operator or numeric operand */
int getop(double *number)
{
  char s[MAXOP];
  int i, c;
  while ((s[0] = c = getch()) == ' ' || c == '\t');
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-' && c != '+')
      return c; /* not a number */
  i = 0;
  if (c == '-' || c == '+') {
    if (!isdigit(c = getch())) {
      ungetch(c);
      return s[i];
    } else
      s[++i] = c;
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()));
  if (c == '.')   /* collect fraction part */
    while (isdigit(s[++i] = c = getch()));
  s[i] = '\0';
  sscanf(s, "%lf", number);
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch (void) /* get a (possibly pushed back) character */
{
  return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
