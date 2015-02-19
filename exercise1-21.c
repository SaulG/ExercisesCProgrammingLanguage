#include<stdio.h>
#define MAXTEXT 10000
#define MAXLINE 1000
#define LINESIZE 40

int getLine(char s[], int lim);
void foldText(char text[], char textFolded[], int lineSize);
int appendText(char line[], char text[], int index);

int main() {
  char text[MAXTEXT];
  char textFolded[MAXTEXT];
  char line[MAXLINE];
  int index = 0;

  while((getLine(line, MAXLINE)) > 0)
    index = appendText(line, text, index);
  text[index] = '\0';

  foldText(text, textFolded, LINESIZE);

  printf("Original text: \n%s\n", text);
  printf("Text folded: \n%s\n", textFolded);

  return 0;
} 

void foldText(char text[], char textFolded[], int lineSize) {
  int index_t = 0;
  int index_tf = 0;
  int counter = 0;

  while(text[index_t] != '\0') {
    if (text[index_t] == '\n') {
      index_t++;
      continue;
    }
    if (counter <= lineSize) {
      textFolded[index_tf] = text[index_t];   
      index_tf++;
      index_t++;
      counter++;
    } else {
      while(text[index_t] != ' ') {
	textFolded[index_tf] = text[index_t];
	index_tf++;
	index_t++;
      }
      textFolded[index_tf] = '\n';
      index_tf++;
      counter = 0;
    }
    
  }
}

int appendText(char line[], char text[], int index) {
  int i = 0;
  while(line[i] != '\0') {
    text[index] = line[i];
    i++;
    index++;
  }
  text[index] = '\n';
  index++;
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
