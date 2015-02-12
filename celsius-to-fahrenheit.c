#include <stdio.h>

main() {
  float celsius, fahr;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 1;

  celsius = lower;
  printf ("Celsius\tFahrenheit\n");
  while (celsius <= upper) {
    fahr = (celsius * ( 9 / 5 ) ) + 32;
    printf ("%.0f\t%.1f\n",celsius, fahr);
    celsius += step;
  }
  
}
