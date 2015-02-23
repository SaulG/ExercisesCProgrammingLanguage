#include<stdio.h>
#define MAXTEXT 10000
#define MAXLINE 1000
#define LINESIZE 40
#define SPACE_TAB 8
#define NUMBERCOLUMNS 1000

int getLine(char s[], int lim);
int appendText(char line[], char text[], int index);
void entab(char text[], int space);

int main() {
  char text[MAXTEXT];
  char line[MAXLINE];
  int index = 0;

  while((getLine(line, MAXLINE)) > 0)
    index = appendText(line, text, index);
  text[index] = '\0';
  printf("Original text: \n%s\n", text);
  entab(text, SPACE_TAB);
  printf("Text entab: \n%s\n", text);

  return 0;
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

void entab(char text[], int space) {
  int wordlength, index_text, index_aux, number_spaces;
  char aux[MAXLINE];  
  wordlength = 0;
  index_text = 0;
  index_aux = 0;

  while(text[index_text] != '\0') {
    switch(text[index_text]) {
    case ' ':
    case '\t':
    case '\n':
      if (wordlength > 0) {
	number_spaces = space - (wordlength % space);
	if (number_spaces >= space)
	  number_spaces += space;
	for (int j = 0; j < number_spaces; j++) {
	  aux[index_aux] = ' ';
	  index_aux++;
	}	     
	wordlength = 0;
      }
      if (text[index_text] == '\n') {
	aux[index_aux] = text[index_text];
	index_aux++;
      }
      break;
    default:
      aux[index_aux] = text[index_text];
      index_aux++;
      wordlength++;
      break;
    }
    index_text++;
  }
  aux[index_aux] = '\0';  
  index_aux = 0;
  index_text = 0;
  while (aux[index_aux] != '\0') {
    text[index_text] = aux[index_aux];
    index_aux++;
    index_text++;
  }
  text[index_text] = '\0';
}
