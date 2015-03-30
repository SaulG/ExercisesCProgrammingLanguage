#include<stdio.h>
#define LIMIT_TEXT 10000
#define LIMIT_LINE 300
void unescape(char original[], char copy[]);
void escape(char original[], char copy[]);
int appendText(char line[], char original[], int index);
int getLine(char line[], int limit);

int main() {
  char original[LIMIT_TEXT];
  char copia[LIMIT_TEXT];
  char line[LIMIT_LINE];
  int index = 0;
  while(getLine(line, LIMIT_LINE) > 0)
    index = appendText(line, original, index);
  original[index] = '\0';
  escape(original, copia);
  printf("Original:\n%s\nCopia:\n %s\n", original, copia);
  unescape(copia, original);
  printf("Copia:\n%s\nOriginal:\n %s\n", copia, original);
  return 0;
}



/**
 void unescape function: 
 Converts visible escape sequences like \n and \t to characters
 like newline and tabs.
**/

void unescape(char original[], char copy[]) {
  int i = 0;
  int j = 0;
  while(original[i] != '\0') {
    if (original[i] == '\\') {
      i++;
      switch(original[i]) {
      case 'n':
	copy[j] = '\n';
	break;
      case 't':
	copy[j] = '\t';
	break;

      }
    } else {
      copy[j] = original[i];
    }
    i++;
    j++;
  }
}


/**
 void escape function: 
 Converts characters like newline and tabs to visible escape
 sequences like \n and \t as it copies the string original
 to copy.
**/
void escape(char original[], char copy[]) {
  int i = 0;
  int j = 0;
  while(original[i] != '\0') {
    switch(original[i]) {
    case '\t':
      copy[j++] = '\\';
      copy[j] = 't';
      break;
    case '\n':
      copy[j++] = '\\';
      copy[j] = 'n';
      break;
    default:
      copy[j] = original[i];
      break;
    }
    i++;
    j++;
  }
}

int appendText(char line[], char original[], int index) {
  int i = 0;
  while (line[i] != '\0') {
    original[index] = line[i];
    index++;
    i++;			       
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



