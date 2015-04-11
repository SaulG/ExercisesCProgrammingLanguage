#include<stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getLine(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);
void reverse(char line[]);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching patterns */
int main() {
  char line [MAXLINE];
  int found = 0;
  while (getLine(line, MAXLINE) > 0) {
    if (strrindex(line, pattern) >= 0) {
      printf("%s", line);
      found++;
    }
  }
  return found;
}

/* getline: get line into s, return length */
int getLine(char s[], int lim) {
  int c, i;
  
  i = 0;
  while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[]) {
  int i, j ,k;
  for (i = 0; s[i] != '\0' ; i++) {
    for (j = i, k = 0; t[k] != '\0' && t[k] == s[j]; j++, k++);
    if (k > 0 && t[k] == '\0')
      return i;
  }
  return -1;
}


/* strrindex: return index of the rightmost match of t in s, -1 if none */
int strrindex(char s[], char t[]) {
  reverse(t);
  reverse(s);
  int i, j, k, total;
  total = i = 0;

  while(s[i++] != '\0')
    total++;

  for (i = 0; s[i] != '\0'; i++){
    for (j = i, k = 0; t[k] != '\0' && t[k] == s[j]; j++, k++);
    if (k > 0 && t[k] == '\0') {
      reverse(s);
      reverse(t);
      printf("%d\n", (total - i) - k);
      return (total - i) - k;
    }
  }
  return -1;
}

void reverse(char s[]) {
  int i, j, max;
  i = j = max = 0;
  char aux[MAXLINE];
  while (s[i] != '\0') {
    aux[i] = s[i];
    ++i;
  }

  while (i != 0) {
    s[j] = aux[i-1];
    --i;
    ++j;
  }
  s[j] = '\0';
  ++j;
}
