#include <stdio.h>

/* echo command-line arguments: 2nd version */
int main(int argc, char *argv[])
{
  printf("number of arguments: %d\n", argc - 1); // argc - 1 because the last is a null pointer
  while (--argc > 0)
    printf("%s%s", *++argv, (argc > 1)? " " : "");
  printf("\n");
  return 0;
}
