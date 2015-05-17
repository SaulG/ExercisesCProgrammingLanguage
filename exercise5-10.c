#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define MAXVAL 10
#define NUMBER '0' /* signal that a number was found */

int gettop(char *valor, char *stack[]);
void push(double);
double pop(void);
int getop(char[]);
int getch(void);
void ungetch(int);

extern int sp;         /* next free stack position */
extern double val[];   /* value stack */
extern int bufp;       /* index of the buffer */


/**
 Exercise 5-10. Write the program expr, which evaluates a reverse Polish
 expression from the command line, where each operator or operand is a
 separate argument. For example,
 
 expr 2 3 4 + *
 
 evaluates 2 x (3+4).
**/
int main(int argc, char *argv[])
{
  int type;
  double op1;
  double op2;
  char *s[MAXOP];
  while (argc-- > 1) {
    *++argv;
    type = gettop(s, argv);
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      op1 = pop() + pop();
      printf("%f\n", op1);
      push(op1);
      break;
    case 'x':
      op1 = pop() * pop();
      printf("%f\n", op1);
      push(op1);
      break;
    case '-':
      op2 = pop();
      op1 = pop() - op2;
      printf("%f\n", op1);
      push(op1);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0) {
	op1 = pop() / op2;
	printf("%f\n", op1);
	push(op1);
      } else
	printf("error: zero divisor\n");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s \n", s);
      break;
    }    
  } 
  return 1;
}

/* gettop: get next operator or numeric operand */
int gettop(char *valor, char *stack[]) {
  int i = 0;
  while ((*stack)[i] == ' ' || (*stack)[i] == '\t')
    i++;
  *valor = ((*stack)[i]);
  if (!isdigit(*valor) && *valor != '.' && *valor != '-' && *valor != '+')
    return *valor; /* not a number */
  valor+=0;
  if (*valor == '-' || *valor == '+') {
    if (!isdigit((*stack)[i]))
      return *valor;
    else
      *valor++ = (*stack)[i++];
  }
  if (isdigit(*valor)) /* collect integer part */
    while (isdigit(*valor++ = (*stack)[i++]));
  if (*valor == '.')   /* collect fraction part */
    while (isdigit(*valor++ = (*stack)[i++]));
  *valor = '\0';
  return NUMBER;
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
