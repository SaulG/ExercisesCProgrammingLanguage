#include <stdio.h>
#define swap(t,x,y) do{t z=x;x=y;y=z;}while(0)

int main(){
  int x = 8;
  int y = 10;
  printf("before swap -- x: %d y: %d\n",x, y);
  swap(int, x, y);
  printf("after swap -- x: %d y: %d\n",x, y);
  return 0;
}
