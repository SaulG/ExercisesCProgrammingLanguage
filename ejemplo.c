
#include <stdio.h>
#include <stdlib.h>

void modifica(char* pedazo) {
  if (pedazo[0] != '\0') {
    pedazo[0] += 1;
    modifica(++pedazo);
  }
  return;
}

int main() {
  char* texto = (char*)malloc(sizeof(char)*5);
  char* copia = texto;
  (*(texto++)) = 'h';
  (*(texto++)) = 'o';
  (*(texto++)) = 'l';
  (*(texto++)) = 'a';
  (*(texto++)) = '\0';
  printf("%s\n", copia);
  modifica(copia);
  printf("%s\n", copia);
  free(copia);
  return 1;
}


