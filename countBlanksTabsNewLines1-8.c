#include <stdio.h>

main() {
  int blanks, tabs, newlines, c;
  blanks = tabs = newlines = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++blanks;
    if (c == '\t')
      ++tabs;
    if (c == '\n')
      ++newlines;
  }
  printf ("Blanks:%d\tTabs:%d\tNewLines:%d\n", blanks, tabs, newlines);
}
