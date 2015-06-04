#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getch.c"

#define MAXWORD 100
#define UNDERSCORED '_'
#define DOUBLE_QUOTES '"'
#define SINGLE_QUOTES '\''
#define GATO '#'
#define COMMENT '\\'
#define ASTERISK '*'
#define BACKSLASH '/'
#define NEWLINE '\n'


#define IN 1
#define OUT 0

void skipcomments();
void skipstrings();

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c, getch(void), char_flag;
  void ungetch(int);
  char *w = word;
  int skip_char_flag = 0;
  
  while (isspace(c = getch()))
    ;
  if (c != EOF)
    *w++ = c;

  if (c == COMMENT)  //possible comments
    skipcomments();
  
  if (c == DOUBLE_QUOTES) //skip strings
    skipstrings();

  if (!isalpha(c) && 
      c != UNDERSCORED &&      
      c != SINGLE_QUOTES) {
    *w = '\0';
    return c;
  } else
    char_flag = (c == SINGLE_QUOTES)? IN : OUT;
       
  for (; --lim > 0; w++) {
    *w = getch();
    if (*w == COMMENT && !skip_char_flag)
      if (char_flag)
	skip_char_flag = IN;
    
    if (*w == SINGLE_QUOTES) { 
      if (char_flag)
	if (skip_char_flag)
	  skip_char_flag = OUT;
	else 
	  char_flag = OUT;
      else
	break;
    }

    if (skip_char_flag && isalnum(*w))
      skip_char_flag = OUT;
      
    if ((!char_flag) && !isalnum(*w) && (*w != UNDERSCORED)) {
      if (*w == SINGLE_QUOTES)
	w++;
      else
	ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
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

/* skipstrings: skip strings */
void skipstrings()
{
  int c;  
  while ((c = getch()) != DOUBLE_QUOTES && c != EOF);  
  ungetch(c);
}


struct tnode {  /* the tree node: */
  char *word;   /* points to the text */
  int count;    /* number of occurrences */
  struct tnode *left; /* left child */
  struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

int characters_group = 6; /* default of the first characters to be commonly in a group */

/* word frequency count */
int main(int argc, char **argv)
{
  int c_value = 0;
  while (--argc > 0) {    
    if (**++argv == '-')
      switch(*++(*argv)) {
      case 'c':
	++(*argv);
	while (*++(*argv) && **argv != EOF)
	  c_value = (10 * c_value) + (*(*argv) - '0');
	characters_group = c_value;
	break;
      default:
	printf("error: this %c flag is not recognized.\nusage: ./a.out -c [number]\n", **argv);
	break;
      }
  }

  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *strdupr(char *);
int strcmp_tree(char *s1, char*s2);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;

  if (p == NULL) {    /* a new word has arrived */
    p = talloc(); /* make a new node */
    p->word = strdupr(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp_tree(w, p->word)) == 0)
    p->count++;  /* repeated word */
    else if (cond < 0) /* less than into left subtree */
      p->left = addtree(p->left, w);
    else        /* greater than into right subtree */
      p->right = addtree(p->right, w);
    return p;
}

int strcmp_tree(char *s1, char *s2)
{
  extern int characters_group;
  int contador = 0;
  while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2 && characters_group != contador) {
    s1++;
    s2++;
    ++contador;
  }
  if (contador == characters_group || *s1 == *s2) {
    return 0;
  } else if (*s1 > *s2)
    return 1;
  else 
    return -1;
}


/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
  }  
}

#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdupr: copies the string given by its argument into a safe place obtained by  a call on malloc. */
char *strdupr(char *s)
{
  char *p;
  
  p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
  if (p != NULL)
    strcpy(p, s);
  return p;
}
