#define NKEYS (sizeof keytab / sizeof(struct key))

struct key {
  char *word;
  int count;
} keytab[] = {
  {"auto", 0},
  {"break", 0},
  {"case", 0},
  {"char", 0},
  {"const", 0},
  {"continue", 0},
  {"default", 0},
  {"return", 0},
  {"unsigned", 0},
  {"void", 0},
  {"volatile", 0},
  {"while", 0}
};

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getch.c"

#define MAXWORD 100
#define UNDERSCORED '_'
#define DOUBLE_COUTES '"'
#define SINGLE_COUTES '\''
#define GATO '#'
#define COMMENT '\\'
#define ASTERISK '*'
#define BACKSLASH '/'
#define NEWLINE '\n'


#define IN 1
#define OUT 0

int getword(char *, int);

struct key *
binsearch(char *, struct key *, int);

void skipcomments();
void skipcontrollines();

/* count C keywords */
int main ()
{
  char word[MAXWORD];
  struct key *p;

  while (getword(word, MAXWORD) != EOF) {
    printf("word: %s\n", word);
    if (isalpha(word[0]))
      if ((p = binsearch(word, keytab, NKEYS)) != NULL)
	p->count++;
  }

  for (p = keytab; p < keytab + NKEYS; p++)
    if (p->count > 0)
      printf("%4d %s\n", p->count, p->word);
  return 0;    
}

/* binsearch: find word in tab[0]...tab[n-1]  */
struct key *binsearch(char *word, struct key *tab, int n)
{
  int cond;
  
  struct key *low = &tab[0];
  struct key *high = &tab[n];
  struct key *mid;
  
  while (low < high) {
    mid = low + (high - low) / 2;
    if ((cond = strcmp(word, mid->word)) < 0)
      high = mid;
    else if (cond > 0)
      low = mid + 1;
    else 
      return mid;
  }
  return NULL;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c, getch(void), string_flag, char_flag;
  void ungetch(int);
  char *w = word;
  int skip_string_flag = 0;
  int skip_char_flag = 0;
  
  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;

  if (c == COMMENT)  //possible comment
    skipcomments();
  
  if (c == GATO) //possible constant
    skipcontrollines();

  if (!isalpha(c) && 
      c != UNDERSCORED && 
      c != DOUBLE_COUTES &&
      c != SINGLE_COUTES) {
    *w = '\0';
    return c;
  } else {
    string_flag = (c == DOUBLE_COUTES)? IN : OUT;
    char_flag = (c == SINGLE_COUTES)? IN : OUT;
  }
       
  for (; --lim > 0; w++) {
    *w = getch();
    if (*w == COMMENT && !skip_char_flag && !skip_string_flag) {
      if (string_flag)
	skip_string_flag = IN;
      else if (char_flag)
	skip_char_flag = IN;
    }
    
    if (*w == DOUBLE_COUTES) {
      if (string_flag)
	if (skip_string_flag)
	  skip_string_flag = OUT;
	else
	  string_flag = OUT;
      else
	if (!char_flag)
	  break;
    }

    if (*w == SINGLE_COUTES) { 
      if (char_flag)
	if (skip_char_flag)
	  skip_char_flag = OUT;
	else 
	  char_flag = OUT;
      else
	if (!string_flag)
	  break;
    }

    if (skip_string_flag && isalnum(*w))
      skip_string_flag = OUT;

    if (skip_char_flag && isalnum(*w))
      skip_char_flag = OUT;
      
    printf("skip char flag: %d skip string flag: %d w: %c \n", skip_char_flag, skip_string_flag, *w);
    if ((!char_flag) && (!string_flag) && !isalnum(*w) && (*w != UNDERSCORED)) {
      if (*w == DOUBLE_COUTES || *w == SINGLE_COUTES)
	*w++;
      else
	ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

/* skipcontrollines: skip the preprocessor control lines */
void skipcontrollines()
{
  int c;
  do {
  while((c = getch()) != NEWLINE && c != EOF);
  } while ((c = getch()) == GATO && c != EOF);
  ungetch(c);  
}

/* skipcomments: skip short and large comments */
void skipcomments()
{
  int c;  
  switch (c = getch()) {
  case COMMENT:
    while ((c = getch()) != NEWLINE && c != EOF);
    ungetch(c);
    break;
  case ASTERISK:
    do {
      while ((c = getch()) != ASTERISK && c != EOF);
    } while ((c = getch()) != BACKSLASH && c != EOF);   
    ungetch(c);
    break;
  default:
    ungetch(c);
    break;
  }
}
