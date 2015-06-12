#include <stdio.h>
#include <string.h>

#define MAXINCIDENCIAS 10000
#define MAXFILES 5
#define MAXLINE 100

enum {OK, FAIL};

typedef struct {
  char *file;
  int line;
} incidencia;

typedef struct {
  FILE *file;
  char *name;
} File;


int findPatternInFiles(char *pattern, File *files[MAXFILES], int numberFiles, incidencia *incidencia_p);
void printIncidencias(incidencia *incidencia_p, int numero_incidencias);
char *strdupr(char *s);

int main(int argc, char *argv[]) 
{
  File *files[MAXFILES];
  File *initial_file_p = files;  
  File *file_p = files;

  char *prog_main = &argv[0];
  char *pattern;

  int numero_incidencias;
  int flag_pattern = FAIL;
  int c;

  /* getting the pattern to find */
  if ((*++argv)[0] == '-') {
    c = *++argv[0];
    switch (c) {
    case 'p':
      pattern = *++argv;
      flag_pattern = OK;
      argc -= 2;  
      break;
    default:
      printf("find: illegal option %c\n", c);
      break;
    }
  }

  /* return 1 if pattern is not defined */
  if (flag_pattern == FAIL) {
    printf("Provide the pattern to search by using -p as flag.\n");
    return 1;
  }

  if (argc == 1){ /* use stdin as input */
    file_p->file = stdin;
    file_p->name = "stdin";    
  } else { /* otherwise check every file name */
    while (--argc > 0) {
      if ((file_p->file = fopen(*++argv, "r")) == NULL){	
	printf("%s: can't open %s\n", prog_main, *argv);		       
      }
      file_p->name = *argv;
      file_p++;
    }
    
  }
  
  incidencia incidencias[MAXINCIDENCIAS];
  incidencia *incidencia_p = incidencias;

  /* find pattern in every file in array */
  numero_incidencias = findPatternInFiles(pattern, files, ((int)(file_p) - (int)(initial_file_p)) / sizeof(File), incidencia_p);

  /* print every match*/
  printIncidencias(incidencias, numero_incidencias);
  return 0;
}


void printIncidencias(incidencia *incidencia_p, int numero_incidencias) {
  while (numero_incidencias-- > 0) {
    printf("Match in file %s at line %d\n", incidencia_p->file, incidencia_p->line);
    incidencia_p++;
  }
}

int findPatternInFiles(char *pattern, File *files[MAXFILES], int numberFiles, incidencia *incidencia)
{
  char lineFile[MAXLINE];
  int numberFile;
  int numberLine;
  int numberIncidencias = 0;
  File *file_p = files;

  for (numberFile = 0; numberFile < numberFiles; numberFile++, file_p++) {
    numberLine = 1;
    while (fgets(lineFile, MAXLINE, file_p->file) != NULL) {
      if ((strstr(lineFile, pattern) != NULL) != 0) {
	incidencia[numberIncidencias].file = file_p->name;
	incidencia[numberIncidencias].line = numberLine;
	numberIncidencias++;
      }      
      numberLine++;
    }
    numberLine = 0;
    fclose(file_p->file);
  }  
  return numberIncidencias;
}
