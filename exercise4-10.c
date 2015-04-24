#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define MAXLINE 100 /* max size of line */
#define NUMBER '0' /* signal that a number was found */

int getop(char[], char[]);
int getLine(char s[]); /* get the line from the input and return the length of the line */
void push(double);
double pop(void);

void pushRecentValue(double); /* push recent value to the stack of recent values */
double popRecentValue(void); /* pop recent value to the stack of recent values */
void printRecentValues(); /* print the recent values from the stack of recent values */

void printTop(); /* print the top of the stack */
void clearStack(); /* clear the stack */
void duplicateTop(); /* duplicate the top of the stack */
void swapTop(); /* swap the two items from the top of the stack */
void ungets(char s[]); /* string value to push back on input */

int index_line = 0;

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
  char line[MAXLINE];
  int limit = 0;
  while ((limit = getLine(line)) > 0) {    
    while ((type = getop(line, s)) != '\0') {
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
      case 'r': /* command to print the recent values */
	printRecentValues();
	break;
      case '\n':
	op1 = pop();
	pushRecentValue(op1);
	printf("\t%.8g\n", op1);
	break;
      default:
	printf("error: unknown command %s \n", s);
	break;
      }
    }
    index_line = 0;
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

#define MAXREC 26 /* max size of the recent values saved */
int rv = 0;       /* index of the recent values stack */
double recentValues[MAXREC]; /* stack of recent values */

/* pushRecentValue: push f value to recent values stack */
void pushRecentValue(double f) {
  if (rv < MAXREC)
    recentValues[rv++] = f;
  else {
    popRecentValue();
    recentValues[rv++] = f;
  }
}

/* popRecentValue: pop value from the recent values stack */
double popRecentValue() {
  if (rv > 0)
    return recentValues[rv--];
  else {
    printf("No recent values available.\n");
    return 0.0;
  }
}

/* printRecentValues: print all the stack of recent values */
void printRecentValues() {
  for (int i = 0; i < rv; i++)
    printf("%g\t", recentValues[i]);
  printf("\n");
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

int getop(char line[], char s[]) {
  int i, c;
  while ((c = s[0] = line[index_line++]) == ' ' || c == '\t');
  s[1] = '\0';
  
  if (!isdigit(c) && c != '.' && c!= '-' && c != '+')
    return c; /* not a number */
  i = 0;
  if (c == '-' || c == '+') {
    if (!isdigit(c = line[index_line++])) {
      index_line--;
      return s[i];
    } else
      s[++i] = c;
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = line[index_line++]));
  if (c == '.')   /* collect fraction part */
    while (isdigit(s[++i] = c = line[index_line++]));
  s[i] = '\0';
  index_line--;
  return NUMBER;  
}

int getLine(char s[]) {
  int c;
  int i = 0;
  while ( (c = getchar()) != EOF && (c != '\n') )
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}
