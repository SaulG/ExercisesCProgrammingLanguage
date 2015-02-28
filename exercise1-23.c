#include <stdio.h>
#define MAXTEXT 10000
#define MAXLINE 1000
#define MAXWORD 200
#define LINESIZE 40
#define IN 0
#define OUT 1
#define YES 1
#define NO 0

int getLine(char s[], int lim);
int appendText(char line[], char text[], int index);
void removeComments(char text[], char newText[]);

int main() {
  char text[MAXTEXT];
  char newText[MAXTEXT];
  char line[MAXLINE];
  int index = 0;

  while((getLine(line, MAXLINE)) > 0)
    index = appendText(line, text, index);
  text[index] = '\0';
  removeComments(text, newText);  
  printf("Comienza remover comentarios:\n%s", newText);
  return 0;
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



void removeComments(char text[], char newText[]) {
  int state_short_comment = OUT;
  int state_long_comment = OUT;
  int state_double_quotation = OUT;
  int state_single_quotation = OUT;
  int ignore_line = NO;
  int index_newText = 0;
  for (int i = 0; text[i] != '\0'; i++) {
    switch(text[i]) {
    case '/':
      if ((state_double_quotation == OUT) &&
	  (state_single_quotation == OUT) &&
	  (state_short_comment == OUT) &&
	  (state_long_comment == OUT)) {	 
	
	if (text[i+1] == '/')
	  state_short_comment = IN;

	if (text[i+1] == '*') 
	  state_long_comment = IN;

      } 
      break;
    case '\n':
      if (state_short_comment == IN) {
	state_short_comment = OUT;
	ignore_line = YES;
      }
      break;
    case '*':
      if ((state_double_quotation == OUT) &&
	  (state_single_quotation == OUT) &&
	  (state_long_comment == IN) &&
	  (state_short_comment == OUT)) {	
	if (text[i+1] == '/') {
	  state_long_comment = OUT;
	  i+=2;
	}
      }
      break;
    case '\"':
      if ((state_double_quotation == OUT) &&
	  (state_single_quotation == OUT) &&
	  (state_long_comment == OUT) &&
	  (state_short_comment == OUT))
	state_double_quotation = IN;
      else 
	state_double_quotation = OUT;
      break;
    case '\'':
      if ((state_single_quotation == OUT) && 
	  (state_short_comment == OUT) &&
	  (state_long_comment == OUT))
	state_single_quotation = IN;
      else
	state_single_quotation = OUT;
      break;
    }
    if (state_long_comment == OUT && 
	state_short_comment == OUT &&
	ignore_line == NO) {
      newText[index_newText] = text[i];
      printf("%c", text[i]);
      index_newText++;
    }
    ignore_line = NO;
  }
}
