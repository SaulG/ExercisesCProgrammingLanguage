#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "strlen.c"

#define MAXLINE 100
#define MAXSIZE 10
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100    /* maximum depth of val stack */
#define MAXOP 100 /* max size of operand or operator */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */

int getop(char *s);
void push(double);
double pop(void);
int getLine(char *s);
int atoiP(char *s);
int strindex(char *text, char *pattern);
char *itoa(int n, char *s);
void reverse(char *s);

int main() {
  char s[MAXLINE];
  int n = getLine(s);
  printf("testing getline ---  size: %d string: %s\n",n, s);

  char *number = "19";
  n = atoiP(number);
  printf("testing atoiP --- string: %s int: %d\n", number, n);
  
  int num = 10;
  char num_str[MAXSIZE];
  itoa(num, &num_str);
  printf("testing atoiP --- int: %d string: %s\n", num, num_str);

  printf("About to testing the function strrindex which it allows you to find a pattern in text returning an index\n");
  char *text = "Buenos dias sr gato";
  char *pattern_1 = "gato";
  printf("Testing text: %s and pattern: %s", text, pattern_1);
  int index = strindex(text, pattern_1);
  printf(" index: %d\n", index);
  char *pattern_2 = "perro";
  printf("Testing text: %s and pattern: %s", text, pattern_2);
  index = strindex(text, pattern_2);
  printf(" index: %d\n", index);

  int type;
  double op2;
  char stack[MAXOP];
  while ((type = getop(stack)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(stack));
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

/* getLine: get the line from the input and return the length of the line. 
*/
int getLine(char *s) {
  int c;
  int i = 0;
  while ((c = getchar()) != EOF && (c != '\n')) {
    *s++ = c;
    i++;
  }
  if (c == '\n') {
    *s++ = c;
    i++;
  }
  *s = '\0';  
  return i;
}

/* atoiP: convert string s to integer i */
int atoiP(char *s) 
{
  int n = 0;
  while (*s >= '0' && *s <= '9') {
    n = (10 * n) + (*s - '0');
    *s++;
  }
  return n;
}

/* itoa: convert n to string s */
char *itoa(int n, char *s) {
  int sign;  
  char *string = s;
  sign = (n < 0)? -1 : 1;
  do {
    *string++ = sign * (n % 10) + '0';
  } while(( n /= 10 ) > 0);
  if (sign < 0)
    *string++ = '-';
  *string = '\0';
  reverse(s);
  printf("s:%s\n", s);
  return string;
}

/* reverse: reverse the order of characters in s */
void reverse(char *s) { 
  char *aux = s;
  char *string = s;
  char temp[MAXSIZE];
  char *temp_p = temp;
  int i = 0;
  while (temp[i] = *aux++)
    i++;
  i--;  
  temp_p += i;
  while(i >= 0){
    *string++ = *temp_p--;    
    i--;
  }
  *string = '\0';  
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t) {
  char *string = s;
  char *pattern = t;
  int i, j, p; 
  for (i = 0; string[i] ; i++) {
    //printf("\nstrindex: %c\n", string[i]);
    for (j = i, p = 0; pattern[p] && string[j] == pattern[p]; j++, p++)
      ; 
    if (pattern[p] == '\0' && i > 0) 
      return i;
  }
  //printf("before sending -1\n");
  return -1;
}

/* gettop: get next operator or numeric operand */
int getop(char *s) {
  int i, c;
  static int last_known = '\0';
  
  if (last_known != '\0') {
    c = last_known;
    last_known = '\0';
  } else
      c = getch();
  while ((*s = c) == ' ' || c == '\t')
    c = getch();
  *++s = '\0';
  if (!isdigit(c) && c != '.' && c != '-' && c != '+')
    return c; /* not a number */
  s+=0;
  if (c == '-' || c == '+') {
    if (!isdigit(c = getch())) {
      last_known = c;
      return *s;
    } else
      *++s = c;
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(*++s = c = getch()));
  if (c == '.')   /* collect fraction part */
    while (isdigit(*++s = c = getch()));
  *++s = '\0';
  if (c != EOF)
    last_known = c;
  return NUMBER;
}

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
