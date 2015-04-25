#include <stdio.h>
#define NUMBER '0' /* signal that a number was found */
void push(double);
double pop(void);
int getop(char[]);
int getch(void);
void ungetch(int);

extern int sp;           /* next free stack position */
extern double val[];   /* value stack */
extern int bufp;      /* index of the buffer */
