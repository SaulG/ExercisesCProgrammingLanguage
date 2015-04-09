#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define LIMIT 100
#define MAXLINE 1000

void reverse(char line[]);
void itob(int n, char s[], int b);

int main(int argc, char **argv) {
  int number, base;
  number = atoi(argv[1]);
  base = atoi(argv[2]);
  char s[LIMIT];
  itob(number, s, base);
  printf("itob(%d) with base %d -> result: %s\n", number, base, s);
}


/**
   void itoa: convert n to characters in s
 **/
void itoa(int n, char s[]) {
  int i, sign;
  sign = (n < 0)? -1 : 1;
  i = 0;
  do {
    s[i++] = sign * (n % 10) + '0';    
  } while ((n /= 10) != 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}


/**
   void itob: convert n to characters in s given a base b

 **/
void itob(int n, char s[], int b) {
  int i;
  i = 0;
  do {
    s[i] = n % b;    
    if (s[i] < 9)
      s[i] = s[i] + '0';
    else
      s[i] = s[i] + ('A' - 10);
    i++;
  } while( ( n /= b ) != 0 );
  s[i] = '\0';
  reverse(s);
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
