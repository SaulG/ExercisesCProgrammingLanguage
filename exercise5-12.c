#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTEXT 10000
#define MAXLINE 1000
#define SPACE_TAB 4
#define MAXSPACE 30

#define NO 0
#define SI 1

int getLine(char s[], int lim);
int appendText(char line[], char text[], int index);
void entab(char *text, int space, int starting_at);
void detab(char *text, int space, int starting_at);


int main(int argc, char *argv[]) 
{
  
  int size_array = 0, index = 0;
  int starting_at, c, space;
  

  //default setting
  space = SPACE_TAB;
  starting_at = 0;
  while (--argc > 0 && (c = (*++argv)[0])) {
      printf("%c\n", c);
      switch (c) {
      case '+':
	//detenerse cada space tab
	space = getNumber(argv);
	break;
      case '-':
	//a partir de la columna tal
	starting_at = getNumber(argv);
	break;
      default:
	printf("Entab - Detab: illegal option %c\n", c);
	argc = 0;
	return -1;
	break;
      }
  }

  printf("detenerse cada space tab %d a partir de la columna %d\n", space, starting_at);
  char line[MAXLINE];
  while (getLine(line, MAXLINE) > 0) {
    detab(&line, space, starting_at);
    printf("***DETAB***\n%s\n***DETAB***\n", line);
    entab(&line, space, starting_at);
    printf("***ENTAB***\n%s\n***ENTAB***\n", line);

  }
  return 1;
}

int getNumber(char *string[]) {
  char valor[MAXSPACE];
  int index_valor = 0;
  int index = 1;
  while (isdigit((*string)[index]))
    valor[index_valor++] = (*string)[index++];
  valor[index_valor] = '\0';
  return atoi(valor);
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

/***
    function that replaces tabs in the input with the 
    proper number of blanks to space to the next tab stop.
 ***/

void detab(char *text, int space, int starting_at){
    char *text_p = text;

  char text_aux[MAXTEXT];  
  char *text_aux_p = text_aux;

  int space_counter = 0;
  int column_counter = 0;
  int text_size = 0;
  while (*text_aux_p++ = *text_p++)
    text_size++;  
  text_p = text;
  text_aux_p = text_aux;
  while (text_size > 0) {
    switch (*text_aux_p) {
    case '\t':
      if (column_counter >= starting_at) {
	for (int i = space_counter % space; i <= space; i ++)
	  *text_p++ = ' ';
	space_counter = 0;
	while (*text_aux_p == '\t') {
	  *text_aux_p++;
	  text_size--;
	}
      } else {
	*text_p++ = ' ';
	space_counter++;
      }
      column_counter++;
      break;
    case '\n':
      space_counter = 0;
      text_size--;
      break;
    default:
      *text_p++ = *text_aux_p++;
      text_size--;
      space_counter++;
      column_counter++;
      break;
    }
  }
}

/*** 
     function that replaces strings of blanks by minimum
     number of tabs and blanks to achieve the same spacing.
***/
void entab(char *text, int space, int starting_at) {
  char *text_p = text;

  char text_aux[MAXTEXT];  
  char *text_aux_p = text_aux;

  int space_counter = 0;
  int column_counter = 0;
  int text_size = 0;
  while (*text_aux_p++ = *text_p++)
    text_size++;  
  text_p = text;
  text_aux_p = text_aux;
  while (text_size > 0) {
    switch (*text_aux_p) {
    case '\t':
    case ' ':      
      if (column_counter >= starting_at) {
	while ((space_counter / space) > 1) {
	  *text_p++ = '\t';
	  space_counter -= space;
	}
	for (int i = space_counter % space; i <= space; i ++)
	  *text_p++ = ' ';
	space_counter = 0;
	while (*text_aux_p == ' ' || *text_aux_p == '\t') {
	  *text_aux_p++;
	  text_size--;
	}
      } else {
	*text_p++ = ' ';
	space_counter++;
      }
      column_counter++;
      break;
    case '\n':
      space_counter = 0;
      text_size--;
      break;
    default:
      *text_p++ = *text_aux_p++;
      text_size--;
      space_counter++;
      column_counter++;
      break;
    }
  }
}
