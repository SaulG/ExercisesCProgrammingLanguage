#include<stdio.h>

int main() {
  int numbers[10][10];
  int (*pointer)[10][10];
  pointer = &numbers;
  int numero = 2;
  for (int i = 0; i< 10; i++) {
    for (int j = 0; j< 10; j++) {
      printf("1 --- imprimiendo i: %d j:%d r: %d\n", i, j, numero * i * j);
      (*pointer)[i][j] = numero * i * j;
    }
  }  

  for (int i = 0; i< 10; i++) {
    for (int j = 0; j< 10; j++) {
      printf("2 --- imprimiendo i: %d j:%d r: %d\n", i, j, (*pointer)[i][j]);
    }
  }

  return 1;
}


