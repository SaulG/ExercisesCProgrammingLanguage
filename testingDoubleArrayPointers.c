#include<stdio.h>

int main() {
  int numbers[10][10];
  int (*numbers_p)[10][10];
  numbers_p = &numbers;
  int numero = 2;
  for (int i = 0; i< 10; i++) {
    for (int j = 0; j< 10; j++) {
      printf("1 --- imprimiendo i: %d j:%d r: %d\n", i, j, numero * i * j);
      (*numbers_p)[i][j] = numero * i * j;
    }
  }  

  for (int i = 0; i< 10; i++) {
    for (int j = 0; j< 10; j++) {
      printf("2 --- imprimiendo i: %d j:%d r: %d\n", i, j, (*numbers_p)[i][j]);
    }
  }

  char characters[10][10];
  char (*characters_p)[10][10];
  characters_p = &characters;
  for (int i = 0; i< 10; i++) {
    for (int j = 0; j< 9; j++) {
      printf("1 --- imprimiendo i: %d j:%d r: %c\n", i, j, 'a');
      (*characters_p)[i][j] = 'a';
    }
    (*characters_p)[i][10] = '\0';
  }  

  for (int i = 0; i< 10; i++) {
    printf("2 --- imprimiendo i: %d r: %s\n", i, (*characters_p)[i]);
  }



  return 1;
}


