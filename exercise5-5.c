#include <stdio.h>
#define MAXSIZE 1000

void strncpyP(char *s, char *ct, int n);
void strncatP(char *s, char *ct, int n);
int strncmpP(char *cs, char *ct, int n);

int main() {
  char s[MAXSIZE] = "testing the function strncopy";
  char *ct = "strncpy cat";
  int n = 4;

  printf("strncatP --- s: %s ct: %s n: %d", s, ct, n);
  strncatP(s, ct, n);
  printf("\nresultado --- s: %s\n", s);
      
  printf("strncpyP --- s: %s ct: %s n: %d", s, ct, n);
  strncpyP(s, ct, n);
  printf("\nresultado --- s: %s\n", s);

  printf("strncmpP --- cs: %s ct: %s n: %d\tresultado --- s: %d\n", s, ct, n, strncmpP(s, ct, n));


  printf("strncatP --- s: %s ct: %s n: %d", s, ct, n);
  strncatP(s, ct, n);
  printf("\nresultado --- s: %s\n", s);

  printf("strncmpP --- cs: %s ct: %s n: %d\tresultado --- s: %d\n", s, ct, n, strncmpP(s, ct, n));

  printf("strncpyP --- s: %s ct: %s n: %d", s, ct, n);
  strncpyP(s, ct, n);
  printf("\nresultado --- s: %s\n", s);

  return 1;
}


/* strncat: concatenate at most n characters of string ct to string s,
   terminate s with '\0'; return s
*/
void strncatP(char *s, char *ct, int n) {
  ct+=n;
  while(*s++);
  *s--;
  while(*s++ = *ct++); 
}


/* strncpy: copy at most n characters of string ct to s; return s.
   Pad with '\0's if t has fewer than n characters.
 */
void strncpyP(char *s, char *ct, int n) {
  ct+=n;
  while((*s++ = *ct++));
  while(n--)
    *s++ = '\0';
  *s = '\0';
}



/* strncmp: compare at most n characters of string cs to string ct;
   return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct.
 */
int strncmpP(char *cs, char *ct, int n) {
  for(ct+=n, cs+=n; *cs++ == *ct++;);
  if (*cs < *ct)
    return 1;
  else if (*cs == *ct)
    return 0;
  else
    return -1;  
}
