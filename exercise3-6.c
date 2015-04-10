#include<stdio.h>
#include<stdlib.h>
#define LIMIT 100
#define MAXLINE 1000

void itoa(int n, char s[], int width);
void reverse(char line[]);

int main(int argc, char ** argv) {
  int x = atoi(argv[1]);
  int width = atoi(argv[2]);
  char s[LIMIT];
  itoa(x, s, width);
  printf("itoa: n -> %d using as width padding -> %d ---- result: %s\n",x, width, s);
  return 1;
}

void reverse(char s[]) {
  int i, j, max;
  i = j = max = 0;
  char aux[MAXLINE];
  while (s[i] != '\0') {
    aux[i] = s[i];
    ++i;
  }

  while (i != 0) {
    s[j] = aux[i-1];
    --i;
    ++j;
  }
  s[j] = '\0';
  ++j;
}
/**
   void itoa function:
   the width argument is the minimum field width that the converted
   number must be padded with blanks on the left.
 **/
void itoa(int n, char s[], int width) {
  int i, sign, count_padding;
  sign = (n < 0)? -1 : 1; 
  i = 0;
  count_padding = 0;
  do {
    s[i++] = (sign * n % 10) + '0';
    count_padding++;
  } while((n /= 10) != 0);

  if (sign < 0) {
    s[i++] = '-';
    count_padding++;
  }

  while (count_padding < width) {
    s[i++] = ' ';
    count_padding++;
  }

  s[i] = '\0';
  reverse(s);
}
