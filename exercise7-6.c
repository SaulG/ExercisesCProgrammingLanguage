#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100

int diffFiles(FILE *, FILE *);
int strcmp_lines(char *, char*);

int main(int argc, char *argv[]) 
{
  int linea; 
  char *prog_main = argv[0]; /* program name for errors */
  char *prog_f1; /* file one */
  char *prog_f2; /* file two */
  
  FILE *fp1;
  FILE *fp2;

  if (argc <= 2){ /* two files needed to run the program */
    printf("Two files needed to run %s\n", prog_main);
    return 0;
  } else {
    if ((fp1 = fopen(*++argv, "r")) == NULL){      
      printf("%s: can't open %s\n", prog_main, *argv);
      exit(1);
    }
    prog_f1 = argv[0];
    if ((fp2 = fopen(*++argv, "r")) == NULL){
      printf("%s: can't open %s\n", prog_main, *argv);
      exit(1);
    }
    prog_f2 = argv[0];
    linea = diffFiles(fp1, fp2);      
    if (linea > 0)
      printf("The file %s and file %s differ at line %d\n", prog_f1, prog_f2, linea);
    fclose(fp1);
    fclose(fp2);
  }  
  return 1;
}


/* diffFiles: return the line where one of the files differs */
int diffFiles(FILE *file1, FILE *file2)
{
  char linef1[MAXLINE];
  char linef2[MAXLINE];
  int lines = 1;
  while (fgets(linef1, MAXLINE, file1) != NULL && fgets(linef2, MAXLINE, file2) != NULL) {
    if (strcmp_lines(linef1, linef2) != 0)
      return lines;
    lines++;
  }
  return -1;
}

/* strcmp_lines: compares two lines and return non-zero if differ */
int strcmp_lines(char *line1, char *line2) 
{
  while(*line1 != '\0' && *line2 != '\0') {
    if (*line1 > *line2)
      return 1;
    else if (*line1 < *line2)
      return -1; 
    line1++;
    line2++;
  }
  return 0;
}
