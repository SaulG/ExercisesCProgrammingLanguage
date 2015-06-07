#include <stdio.h>
#include <ctype.h>

#define TOLOWER 'l'
#define TOUPPER 'u'

#define OPTION_LOWER 1
#define OPTION_UPPER 2

int main(int argc, char **argv) /* lower: convert input to lower case */
{
  int c;
  int option;
  while (argc-- > 1) {
    if (**++argv == '-') {
      switch(*++(*argv)) {
      case TOLOWER:
	option = OPTION_LOWER;
	break;
      case TOUPPER:
	option = OPTION_UPPER;
	break;
      default:
	printf("error: this %c flag is not recognized\n", **argv);
	break;
      }
    }
  }

  while ((c = getchar()) != EOF) {
    switch(option) {
    case OPTION_UPPER:
      putchar(toupper(c));
      break;
    case OPTION_LOWER:
      putchar(tolower(c));
      break;
    }     
  }  
  return 0;
}
