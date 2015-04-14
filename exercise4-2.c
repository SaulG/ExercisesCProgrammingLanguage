#include<stdio.h>
#include<ctype.h>

double atof(char s[]);

/* Call atof which converts strings to doubles
   by using an argument when running the program.
*/
int main(int argc, char ** argv) {
  printf("%f\n", atof(argv[1]));
  return 1;
}

/* atof: convert string s to double 
   This version accepts scientific notation like 12.3e-3
*/
double atof(char s[])
{
  double val, power, exp;
  int i, sign, sign_exp;

  for (i = 0; isspace(s[i]); i++) /* skip white space */
    ;
  sign = (s[i] == '-')? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    s++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]) || s[i] == 'e'; i++) {
    if (s[i] == 'e') {
      i++;
      sign_exp = (s[i] == '-')? -1 : 1;
      if (s[i] == '+' || s[i] == '-')
	i++;  
      for (exp = 0; isdigit(s[i]); i++)
	exp = 10 * exp + (s[i] - '0');     
      while(exp > 0) {
	exp--;
	if (sign_exp < 0)
	  power *= 10.0;
	else 
	  power /= 10.0;
      }      
    } else {
      val = 10.0 * val + (s[i] - '0');
      power *= 10.0;
    }
  }
  return sign * val / power;
}


