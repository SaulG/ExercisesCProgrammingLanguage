#include <stdio.h>
#define MAXTEXT 10000
#define MAXLINE 1000
#define IN 0
#define OUT 1
#define MAXSTACK 1000

int getLine(char s[], int lim);
int appendText(char line[], char text[], int index);
void checkCprogram(char program[]);

int main() {
  char text[MAXTEXT];
  char line[MAXLINE];
  int index = 0;

  while((getLine(line, MAXLINE)) > 0)
    index = appendText(line, text, index);
  text[index] = '\0';
  printf("Original text: \n%s\n", text);
  checkCprogram(text);
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

void checkCprogram(char program[]) {
  int state_parenthesis = 0;
  int state_brackets = 0;
  int state_braces = 0;
  int state_double_quotation = 0;
  int state_single_quotation = 0;
  int state_short_comment = OUT;
  int state_long_comment = OUT;
  
  int last_line_parenthesis = 0;
  int last_line_brackets = 0;
  int last_line_braces = 0;
  int last_line_double_quotation = 0;
  int last_line_single_quotation = 0;
  int last_line_short_comment = 0;
  int last_line_long_comment = 0;
  
  int number_line = 1;

  for(int i = 0; program[i] != '\0'; i++) {
    switch(program[i]) {
    case '(':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  state_long_comment == OUT) {
	state_parenthesis += 1;
	last_line_parenthesis = number_line;
      }
      break;
    case ')':      
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  state_long_comment == OUT) {
	state_parenthesis -= 1;
	last_line_parenthesis = number_line;
      }
      break;
    case '{':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  state_long_comment == OUT) {
	state_brackets += 1;
	last_line_brackets = number_line;
      }
      break;
    case '}':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  state_long_comment == OUT) {
	state_brackets -= 1;      
	last_line_brackets = number_line;
      }
      break;
    case '[':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  state_long_comment == OUT) { 	
	state_braces += 1;
	last_line_braces = number_line;
      }
      break;
    case ']':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  state_long_comment == OUT) {
	state_braces -= 1;
	last_line_braces = number_line;
      }
      break;
    case '\"':
      state_double_quotation += 1;
      last_line_double_quotation = number_line;
      break;
    case '\'':
      state_single_quotation += 1;
      last_line_single_quotation = number_line;
      break;
    case '\n':
      if (state_short_comment == IN)
	state_short_comment = OUT;
      number_line += 1;
      break;
    case '/':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT) {
	
	if (program[i+1] == '/') {
	  state_short_comment = IN;
	  last_line_short_comment = number_line;
	}

	if (program[i+1] == '*') {
	  state_long_comment = IN;	  
	  last_line_long_comment = number_line;
	}
	
      }
      break;
    case '*':
      if (state_double_quotation % 2 == 0 &&
	  state_single_quotation % 2 == 0 &&
	  state_short_comment == OUT &&
	  program[i+1] == '/')
	  state_long_comment = OUT;      
      break;
    }
  }

  printf("Status:\n");
  if (state_parenthesis == 0)
    printf("Parenthesis: OK\n");
  else 
    printf("Parenthesis: Fail\t Number of line: %d\n", last_line_parenthesis);
  
  if (state_brackets == 0)
    printf("Brackets: OK\n");
  else
    printf("Brackets: Fail\t Number of line: %d\n", last_line_brackets);
  
  if (state_braces == 0)
    printf("Braces: OK\n");
  else 
    printf("Braces: Fail\t Number of line: %d\n", last_line_braces);
  
  if (state_double_quotation % 2 == 0)
    printf("Double Quotation: OK\n");
  else
    printf("Double Quotation: Fail\t Number of line: %d\n",last_line_double_quotation);

  if (state_single_quotation % 2 == 0)
    printf("Single Quotation: OK\n");
  else 
    printf("Single Quotation: Fail\t Number of line: %d\n", last_line_single_quotation);

  if (state_long_comment == OUT)
    printf("Balanced Long Comment: OK\n");
  else
    printf("Balanced Long Comment: Fail\t Number of line: %d\n", last_line_long_comment);

}
