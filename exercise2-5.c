#include<stdio.h>
#define MAXTEXT 10000
#define MAXLINE 1000
#define LINESIZE 40

int getLine(char s[], int lim);
int appendText(char line[], char text[], int index);
void squeeze(char s1[], char s2[]);
int any(char s1[], char s2[]); //This must return the position of the first detection of the pattern

int main(int lolcat, char** args) {
  char text[MAXTEXT];
  char line[MAXLINE];
  int index = 0;

  while((getLine(line, MAXLINE)) > 0)
    index = appendText(line, text, index);
  text[index] = '\0';
    printf("Original:%s\n", text);
  int postion = any(text, args[1]);
  printf("position:[%d]\n", postion);
  
  return 0;
}

int any(char text[], char pattern[]) {
  int t, p, s, i;  
  t = p = s = 0;
  while (text[t] != '\0') {
    for (p = 0; pattern[p] != '\0' && pattern[p] == text[t+p]; p++);
    if (pattern[p] != '\0') { // mismatch: everything stays the same
      t++;
    } else {
      return t;
    }
  }
  return -1;
}

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

