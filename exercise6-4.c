#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getch.c"

#define MAXWORD 100
#define MAXLINES 100

int total_nodes = 0;
struct tnode **array_of_nodes;

/* getword: get next word or character from input */
int getword(char *word, int lim)
{

  int c, getch(void);
  void ungetch(int);  
  char *w;
  w = word;
  while (isspace(c = getch()))
    ;
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
  *w = '\0';
  return word[0];
}

struct tnode {  /* the tree node: */
  char *word;   /* points to the text */
  int count; /* frequency of occurrence */
  struct tnode *left; /* left child */
  struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
void arrayNodesPrint(struct tnode**, int);
void treeNodesToArray(struct tnode*);
void qsort1(void **v, int left, int right, int (*comp)(void *, void *));
int numcmp(const struct tnode *s1, const struct tnode *s2);

/* word frequency count */
int main()
{
  struct tnode *root;
  char word[MAXWORD];
  
  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);

  array_of_nodes = malloc(total_nodes * sizeof(struct tnode*));  
  struct tnode** inicio = array_of_nodes;
  treeNodesToArray(root);
  qsort1((void **)inicio, 0, total_nodes-1, (int (*)(void *, void*))numcmp);
  arrayNodesPrint(inicio, total_nodes);
  free(inicio);
  return 0;
}

void arrayNodesPrint(struct tnode**p, int largo) {
  for (int i = 0; i < largo; i++) {
    printf("Count: %d Word: %s\n", p[i]->count, p[i]->word);
  }
}


struct tnode *talloc(void);
char *strdupr(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
  extern int total_nodes;
  int cond;
  if (p == NULL) {    /* a new word has arrived */
    p = talloc(); /* make a new node */
    p->word = strdupr(w);
    p->count = 1;    
    p->left = p->right = NULL;
    total_nodes++;
  } else if ((cond = strcmp(w, p->word)) == 0) 
    p->count++; /* repeated word */
  else if (cond < 0) /* less than into left subtree */
    p->left = addtree(p->left, w);
  else        /* greater than into right subtree */
    p->right = addtree(p->right, w);
  return p;
}


void treeNodesToArray(struct tnode* p)
{
  if (p == NULL){
    return;
  }
  treeNodesToArray(p->left);
  treeNodesToArray(p->right);
  *array_of_nodes = p;
  array_of_nodes++;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%s %d\n", p->word, p->count);
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


/* qsort1: sort v[left]...v[right] into increasing order */
void qsort1(void **v, int left, int right, int (*comp)(void *, void *))
{
  extern int reverse;
  int i, last;
  void swap(void **v, int, int);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++) {    
      if ((*comp)(v[i], v[left]) > 0)
	swap(v, ++last, i);
  }
  swap(v, left, last);
  qsort1(v, left, last-1, comp);
  qsort1(v, last+1, right, comp);
}


int numcmp(const struct tnode *s1, const struct tnode *s2)
{
  return s1->count - s2->count;
}

void swap(void **v, int i, int j)
{
  void *temp;
  
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
