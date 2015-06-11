#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define LIMITE 1000

typedef enum { 
  DECIMAL_INTEGER, 
  INTEGER, 
  OCTAL_INTEGER, 
  UNSIGNED_DECIMAL_INTEGER,
  HEXADECIMAL_INTEGER,
  CHARACTERS,
  STRINGS,
  FLOATING_POINT
} Tipo;

typedef struct {
  Tipo tipo;
  union {
    int ival;
    unsigned int uival;
    char cval;
    char *sval;
    double dval;
  } value;
} variable;

variable * minscanf(char *, ...);
char *strdupr(char *);
int sizeOfArrayVariables;

int main() {
  extern int sizeOfArrayVariables;
  variable *x;
  x = minscanf("%d\t%s\t%d%g%c%u%x%o%i\n", 10, "LOLCAT", 20, 30.092, 'u', 4294967295, 15, 9, 10);
  for(int i = 0; i < sizeOfArrayVariables; i++, x++) {
    switch(x->tipo) {
    case DECIMAL_INTEGER:
      printf("tipo: decimal integer value: %d\n", x->value.ival);
      break;
    case INTEGER:
      printf("tipo: integer value: %i\n", x->value.ival);
      break;
    case OCTAL_INTEGER:
      printf("tipo: octal integer value: %o\n", x->value.uival);
      break;
    case UNSIGNED_DECIMAL_INTEGER:
      printf("tipo: unsigned decimal integer value: %u\n", x->value.uival);
      break;
    case HEXADECIMAL_INTEGER:
      printf("tipo: hexadecimal integer value: %x\n", x->value.ival);
      break;
    case CHARACTERS:
      printf("tipo: characters value: %c\n", x->value.cval);
      break;
    case STRINGS:
      printf("tipo: strings value: %s\n", x->value.sval);
      break;
    case FLOATING_POINT:
      printf("tipo: floating point value: %g\n", x->value.dval);      
      break;
    }
  }
  return 0;
}

/* minscanf: minimal scanf with variable argument list */
variable * minscanf(char *fmt, ...)
{
  static variable variables[LIMITE];
  extern int sizeOfArrayVariables;
  variable *variable_p = variables;
  variable *initial_pointer = variable_p;

  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;  
  int ival;
  unsigned int uival;
  double dval;    

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    } 
    switch (*++p) {
    case 'd':
      ival = va_arg(ap, int);      
      variable_p->tipo = DECIMAL_INTEGER;
      variable_p->value.ival = ival;
      variable_p++;
      break;
    case 'i':
      ival = va_arg(ap, int);      
      variable_p->tipo = INTEGER;
      variable_p->value.ival = ival;
      variable_p++;
      break;
    case 'o':
      uival = va_arg(ap, unsigned int);
      variable_p->tipo = OCTAL_INTEGER;
      variable_p->value.uival = uival;
      variable_p++;
      break;
    case 'x':
      ival = va_arg(ap, int);
      variable_p->tipo = HEXADECIMAL_INTEGER;
      variable_p->value.ival = ival;
      variable_p++;
      break;
    case 'u':
      uival = va_arg(ap, unsigned int);
      variable_p->tipo = UNSIGNED_DECIMAL_INTEGER;
      variable_p->value.uival = uival;
      variable_p++;
      break;
    case 'c':
      ival = va_arg(ap, int);
      variable_p->tipo = CHARACTERS;
      variable_p->value.cval = ival;
      variable_p++;
      break;
    case 'e':
    case 'g':
    case 'f':
      dval = va_arg(ap, double);
      variable_p->tipo = FLOATING_POINT;
      variable_p->value.dval = dval;
      variable_p++;
      break;
    case 's':
      sval = va_arg(ap, char *);
      variable_p->tipo = STRINGS;
      variable_p->value.sval = strdupr(sval);
      variable_p++;
      break;
    default:
      //nothing to do here
      break;
    }
  }  
  sizeOfArrayVariables = ( (int)variable_p - (int)initial_pointer ) / sizeof(variable); //size of array of struct variables
  return variables;
}

/* strdupr: copies the string given by its argument into a safe place obtained by  a call on malloc. */
char *strdupr(char *s)
{
  char *p;
  
  p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
  if (p != NULL)
    strcpy(p, s);
  return p;
}
