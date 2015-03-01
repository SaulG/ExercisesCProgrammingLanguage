#include <stdio.h>

#define MAXDIGITS 1000

int htoi(char s[]);
int getValueHex(char s);
int exponent(int base, int n);

int main(){
  printf("Hexadecimal %s - Decimal %d \n", "0xFFFFFFF", htoi("0xFFFFFFF"));
  return 1;
}

int getValueHex(char s) {
  int n = 0;
  if (s >= '0' && s <= '9') {
    n = (10 * n) + (s - '0');
    return n;
  }
  switch (s) {
  case 'a':
  case 'A':
    n = 10;
    break;
  case 'b':
  case 'B':
    n = 11;
    break;
  case 'c':
  case 'C':
    n = 12;
    break;
  case 'd':
  case 'D':
    n = 13;
    break;
  case 'e':
  case 'E':
    n = 14;
    break;
  case 'f':
  case 'F':
    n = 15;
    break;
  default:
    n = -1;
    break;
  }
  return n;
}

int htoi(char s[]) {
  int start_hexadecimal = 0;
  int total = 0;
  int aux = 0;
  int i = 0;
  int contador = 0;
  
  int valores[MAXDIGITS];
  
  while (s[i] != '\0') {
    if (start_hexadecimal) {      
      aux = getValueHex(s[i]);	
      if (aux < 0) {
	return -1;
      } else {
	printf("Examine: %c\t value: %d\n",s[i], aux);
	valores[contador] = aux;
	contador++;
      }
    }
    if (s[i] == '0' &&
	(s[i+1] == 'x' ||
	 s[i+1] == 'X')) {
      start_hexadecimal = 1;
      i++;
    }
    i++;    
  }
  contador -= 1;
  for (int j = contador; j >= 0; j--)
    total += valores[j] * exponent(16, (contador - j));
  return total;
}

int exponent(int base, int n){
  if (n == 0)
    return 1;
  else 
    return exponent(base, n - 1) * base;
}

