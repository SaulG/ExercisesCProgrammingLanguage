#include<stdio.h>

float fahrenheitToCelsius(float fahr);
float celsiustoFahrenheit(float celsius);

int main() {
  float celsius, fahr, lower, upper, step;
  lower = 0;
  upper = 300;
  step = 1;

  celsius = lower;
  while (celsius <= upper) {
    printf("celsius: %.2f fahrenheit: %.2f\n", celsius, celsiustoFahrenheit(celsius));
    celsius += step;
  }
  printf("\n\n\n\n");
  fahr = lower;
  while (fahr <= upper) {
    printf("fahrenheit: %.2f celsius: %.2f\n", fahr, fahrenheitToCelsius(fahr));
    fahr += step;
  }
  return 0;
}

float fahrenheitToCelsius(float fahr) {  
  return ( 5.0 / 9.0 ) * ( fahr - 32.0 );
}

float celsiustoFahrenheit(float celsius) {
  return ( celsius * ( 9.0 / 5.0 ) ) + 32;
}
