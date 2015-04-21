#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
void printTop(); /* print the top of the stack */
void clearStack(); /* clear the stack */
void duplicateTop(); /* duplicate the top of the stack */
void swapTop(); /* swap the two items from the top of the stack */

/* swapTop: swap the two items from the top of stack */
void swapTop() {
  double item1 = pop();
  double item2 = pop();
  push(item1);
  push(item2);
}

/* duplicateTop: duplicate top of the stack */
void duplicateTop() {
  double item = pop();
  push(item);
  push(item);
}

/* reverse Polish calculator */
int main () {
  int type;
  double op1, op2;
  char s[MAXOP];
  
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
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
    case 'c': /* command to call clearStack() */
      clearStack();
      break;
    case 'p': /* command to call printTop() */
      printTop();
      break;
    case 's': /* command to call swapTop() */
      swapTop();
      break;
    case 'd': /* command to call duplicateTop() */
      duplicateTop();
      break;
    case 'q': /* sine of x's value */
      push(sin(pop()));
      break;
    case 'e': /* exponencial function */
      push(exp(pop()));
      break;
    case 'w': /* pow function */
      op2 = pop();
      op1 = pop();
      if (op1 >= 0.0 && op2 >= 0.0)
	push(pow(op1, op2));
      else
	printf("error: numbers must be positive\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s \n", s);
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

/* printTop: print the top of the stack */
void printTop(void) {
  if (sp < 0)
    printf("error: stack empty\n");
  else
    printf("top value from stack: %g\n", val[sp]);
}

/* clearStack: clear the elements from the stack */
void clearStack(void) {
  sp = 0;
}


#include <ctype.h>
void ungetch();
/*getop: get next operator or numeric operand */
int getop(char s[])
{
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
