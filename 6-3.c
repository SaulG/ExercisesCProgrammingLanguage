#include <stdio.h>

//just to get the size of the array of keytab
#define NKEYS (sizeof keytab / sizeof(struct key))

//another way to write it, by dividing the array size
// by the size of a specific element
//#define NKEYS (sizeof keytab / sizeof keytab[0])

//cannot be used with #if line because the preprocessor 
//does not parse type names


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
  {"unsigned", 0},
  {"void", 0},
  {"volatile", 0},
  {"while", 0}
};

int main() {
  //representation of two parallel arrays of a keyword and keycount
  char *keyword[NKEYS];
  int keycount[NKEYS];
  
  //can be represented as the following structure declaration
  struct key {
    char *word;
    int count;
  } keytab[NKEYS];

  //or like this
  struct key {
    char *word;
    int count;
  };

  struct key keytab[NKEYS];
  return 0;
}
