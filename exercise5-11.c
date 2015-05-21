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
void entab(char *text, int *space);
void detab(char *text, int *space);


int main(int argc, char *argv[]) 
{
  
  int toma_valores = NO;
  int variables[MAXSPACE];
  int *variables_p = &variables;
  int size_array = 0, index = 0;
  int c;
  
  //default setting
  *variables_p = SPACE_TAB;

  while (--argc > 1 && (*++argv)[0] == '-') {
    while (c = *++argv[0]) {
      switch (c) {
      case 't':
	toma_valores = SI;
	break;
      default:
	printf("Entab - Detab: illegal option %c\n",c);
	argc = 0;
	return -1;
	break;
      }
    }
  }

  if (toma_valores == SI) {
    while (isdigit((*argv)[index]) || (*argv)[index] == ',') {
      char valor[MAXSPACE];
      int index_valor = 0;      
      while (isdigit((*argv)[index]))
	valor[index_valor++] = (*argv)[index++];
      valor[index_valor] = '\0';      
      *variables_p++ = atoi(valor);      
      index++;
    }      
  }
  *variables_p = -1;
  
  variables_p = &variables[0];
  while (*variables_p != -1)
    printf("variables: %d\n", *variables_p++);
  
  variables_p = &variables[0];
  char line[MAXLINE];
  while (getLine(line, MAXLINE) > 0) {
    entab(&line, variables_p);
    printf("%s", line);
  }
  return 1;
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

void detab(char *text, int *space){
    char *text_p = text;

  char text_aux[MAXTEXT];  
  char *text_aux_p = text_aux;

  int space_counter = 0;
  int text_size = 0;
  while (*text_aux_p++ = *text_p++)
    text_size++;  
  text_p = text;
  text_aux_p = text_aux;
  while (text_size > 0) {
    switch (*text_aux_p) {
    case '\t':
      for (int i = space_counter % *space; i <= *space; i ++)
  	*text_p++ = ' ';
      if (*space != -1)
	*space++;
      space_counter = 0;
      while (*text_aux_p == '\t') {
	*text_aux_p++;
  	text_size--;
      }
      break;
    case '\n':
      space_counter = 0;
      text_size--;
      break;
    default:
      *text_p++ = *text_aux_p++;
      text_size--;
      space_counter++;
      break;
    }
  }
}

/*** 
     function that replaces strings of blanks by minimum
     number of tabs and blanks to achieve the same spacing.
***/
void entab(char *text, int *space) {
  char *text_p = text;

  char text_aux[MAXTEXT];  
  char *text_aux_p = text_aux;

  int space_counter = 0;
  int text_size = 0;
  while (*text_aux_p++ = *text_p++)
    text_size++;  
  text_p = text;
  text_aux_p = text_aux;
  while (text_size > 0) {
    switch (*text_aux_p) {
    case '\t':
    case ' ':      
      while ((space_counter / *space) > 1) {
	*text_p++ = '\t';
	space_counter -= *space;
      }
      for (int i = space_counter % *space; i <= *space; i ++)
	*text_p++ = ' ';
      if (*space != -1)
	*space++;
      space_counter = 0;
      while (*text_aux_p == ' ' || *text_aux_p == '\t') {
	*text_aux_p++;
  	text_size--;
      }
      break;
    case '\n':
      space_counter = 0;
      text_size--;
      break;
    default:
      *text_p++ = *text_aux_p++;
      text_size--;
      space_counter++;
      break;
    }
  }
}


