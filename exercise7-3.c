#include <stdio.h>
#include <stdarg.h>

void minprintf(char *, ...);

int main() {
  minprintf("%d\t%s\n", 10, "LOLCAT");
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival, flag_format;
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
      printf("%d", ival);
      break;
    case 'i':
      ival = va_arg(ap, int);
      printf("%i", ival);
      break;
    case 'o':
      uival = va_arg(ap, unsigned int);
      printf("%o", uival);
      break;
    case 'x':
      uival = va_arg(ap, unsigned int);
      printf("%x", uival);
      break;
    case 'X':
      uival = va_arg(ap, unsigned int);
      printf("%X", uival);
      break;
    case 'u':
      uival = va_arg(ap, unsigned int);
      printf("%u", uival);
      break;
    case 'c':
      ival = va_arg(ap, int);
      printf("%c", ival);
      break;
    case 'e':
      dval = va_arg(ap, double);
      printf("%e", dval);
      break;
    case 'E':
      dval = va_arg(ap, double);
      printf("%E", dval);
      break;
    case 'g':
      dval = va_arg(ap, double);
      printf("%g", dval);
      break;
    case 'G':
      dval = va_arg(ap, double);
      printf("%G", dval);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case '%':
      printf("%%");
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
	putchar(*sval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
}
