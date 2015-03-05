#include<stdio.h>
#define MAXTEXT 10000
#define MAXLINE 1000
#define LINESIZE 40

int getLine(char s[], int lim);
int appendText(char line[], char text[], int index);
void squeeze(char s1[], char s2[]);

int main(int lolcat, char** args) {
  char text[MAXTEXT];
  char line[MAXLINE];
  int index = 0;

  while((getLine(line, MAXLINE)) > 0)
    index = appendText(line, text, index);
  text[index] = '\0';
    printf("Original:%s\n", text);
  squeeze(text, args[1]);
  printf("Reemplazado:[%s]\n", text);
  
  return 0;
}

/* void squeeze(char text[], char pattern[]) {
  int t, p, s, i;  
  t = p = s = 0;
  while (text[t] != '\0') {
    for (p = 0; pattern[p] != '\0' && pattern[p] == text[t+p]; p++);
    if (pattern[p] != '\0') { // mismatch: everything stays the same
      for (i = 0; i <= p; i++) { // SUPPOSING THAT A PARTIAL MATCH MAY NOT CONTAIN A PREFIX OF A POTENTIAL MATCH
	text[s++] = text[t+i];
	printf("%c", text[t+i]);
      }
      t += p + 1; // skip p characters that were already preserved
    } else { 
      t += p; // skip p characters (but not the termination char)
    }
  }
  text[s] = '\0';
  printf("\n");
  } */




void squeeze(char text[], char pattern[]) {
  int t, p, s, i;  
  t = p = s = 0;
  while (text[t] != '\0') {
    for (p = 0; pattern[p] != '\0' && pattern[p] == text[t+p]; p++);
    if (pattern[p] != '\0') { // mismatch: everything stays the same
      text[s++] = text[t];
      t++;
    } else {
      t += p; // skip p characters (but not the termination char)
    }
  }
  text[s] = '\0';
  printf("\n");
}


int appendText(char line[], char text[], int index) {
  int i = 0;
  while(line[i] != '\0') {
    text[index] = line[i];
    i++;
    index++;
  }
  return index;
} 

int getLine(char line[], int lim) {
  int i, c;
  for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;
  if (c == '\n') {
    line[i] = c;
    i++;
  }
  line[i] = '\0';
  return i;
}

