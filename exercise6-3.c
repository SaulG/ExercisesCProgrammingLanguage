#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getch.c"

#define MAXWORD 100
#define MAXLINES 100
#define MINWORD 4
#define NEWLINE '\n'

int count_lines = 1;

/* getword: get next word or character from input */
int getword(char *word, int lim)
{

  extern int count_lines;
  int c, getch(void);
  void ungetch(int);  
  char *w;
  do {
    w = word;
    while (c = getch()) {
      if (c == NEWLINE)
	count_lines++;      
      if (!isspace(c))
	break;
    }
    if (c != EOF)
      *w++ = c;

    if (!isalpha(c)) {
      *w = '\0';
      return c;
    }

    for (; --lim > 0; w++) {
      *w = getch();
      if (!isalnum(*w)) {
	ungetch(*w);
	break;
      }
    }
  } while (MINWORD >= (((int) w)) - ((int) word));
  *w = '\0';
  return word[0];
}

struct tnode {  /* the tree node: */
  char *word;   /* points to the text */
  int lines[MAXLINES];    /* lines where occur the word */
  int index;
  struct tnode *left; /* left child */
  struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

/* word frequency count */
int main()
{
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

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;

  if (p == NULL) {    /* a new word has arrived */
    p = talloc(); /* make a new node */
    p->word = strdupr(w);
    p->index = 0;    
    p->lines[p->index++] = count_lines;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    if (p->lines[p->index - 1] != count_lines)
      p->lines[p->index++] = count_lines;  /* repeated word */
  } else if (cond < 0) /* less than into left subtree */
      p->left = addtree(p->left, w);
    else        /* greater than into right subtree */
      p->right = addtree(p->right, w);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("word: %s --- at line: ", p->word);
    for (int i = 0; i < p->index; i++)
      printf((i < p->index - 1) ? "%4d, " : "%4d\n", p->lines[i]);
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
