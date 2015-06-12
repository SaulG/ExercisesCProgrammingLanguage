#include <stdio.h>
#include <string.h>

#define MAXINCIDENCIAS 10000
#define MAXFILES 5
#define MAXLINE 100

typedef struct {
  FILE *file;
  char *name;
} File;


void printFiles(File *files[MAXFILES], int numberFiles);
char *strdupr(char *s);

int main(int argc, char *argv[]) 
{
  File *files[MAXFILES];
  File *initial_file_p = files;  
  File *file_p = files;

  char *prog_main = &argv[0];

  if (argc == 1){ /* use stdin as input */
    return 1;
  } else { /* otherwise check every file name */
    while (--argc > 0) {
      if ((file_p->file = fopen(*++argv, "r")) == NULL){	
	printf("%s: can't open %s\n", prog_main, *argv);		       
      }
      file_p->name = *argv;
      file_p++;
    }    
  }

  /* print every file*/
  printFiles(files, ((int)(file_p) - (int)(initial_file_p)) / sizeof(File));
  return 0;
}


void printFiles(File *files[MAXFILES], int numberFiles) {
  File *file_p = files;
  char *line[MAXLINE];
  int numberFile;
  for (numberFile = 0; numberFile < numberFiles; numberFile++, file_p++) {
    printf("File: %s Page: %d\n", file_p->name, numberFile+1);    
    while (fgets(line, MAXLINE, file_p->file) != NULL) {
      printf("%s\n", line);
    }
    printf("-----------------------------------------\n");    
    fclose(file_p->file);
  }  
}
