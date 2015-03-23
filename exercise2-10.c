#include<stdio.h>

int lowerV2(int c);



int main(){
  int a = 'A';
  printf("lowerV2(%c)->%c\n", a, lowerV2(a));
  return 0;
}

int lowerV2(int c) {  
  return (c >= 'A' && c <= 'Z')? c + 'a' - 'A': c;
}
