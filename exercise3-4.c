#include<stdio.h>
#include<limits.h>
#define LIMIT 100
#define MAXLINE 1000

void reverse(char line[]);
void itoa(int n, char s[]);

int main() {
  char s[LIMIT];
  itoa(INT_MIN, s);
  printf("The minimum value of INT = %d\n", INT_MIN);  
  printf("integer -> %d\ncharacters -> %s\n", INT_MIN, s);
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
