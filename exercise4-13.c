#include<stdio.h>
#include<stdlib.h>
#define LIMIT 10
#define MAXLINE 10

void reverse(char line[]);
void itoa(int n, char s[]);

int main(int argc, char **argv) {
  char s[LIMIT];
  int number;
  number = atoi(argv[1]);
  itoa(number, s);
  printf("Number: %d String: %s\n",number, s);
}

/* itoa: convert n to characters in s, in a recursive way. */
void itoa(int n, char s[]) {
  int static i = 0;
  int sign;
  sign = (n < 0)? -1 : 1;
  s[i++] = sign * (n % 10) + '0';
  if ((n / 10) != 0) {
    n /= 10;
    itoa(n, s);
  } else {
    if (sign < 0)
      s[i++] = '-';
    s[i] = '\0';
    reverse(s);
  }
}

/* reverse: reverse the order of characters in s */
void reverse(char s[]) {
  int static i = 0;
  int static j = 0;
  int static state = 1;
  char static aux[MAXLINE];
  if (state) {
    while (s[i] != '\0') {
      aux[i] = s[i];
      i++;
    }
    aux[i] = '\0';
    i--;
    state = 0;   
  }
  if (i >= 0) {
    s[j++] = aux[i--];
    reverse(s);
  } else {
    s[j] = '\0';
  }
}
