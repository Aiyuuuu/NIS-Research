#include "stdio.h"
#include "stdlib.h"
#include "wctype.h"
#include "stdbool.h"
#include "string.h"
#include "unistd.h"

bool W = false;
bool L = false;
bool C = false;

int CHARS_EXCLUDED = 0;;
int WORDS_EXCLUDED = 0;

int TOTAL_WORDS = 0;
int TOTAL_LINES = 0;
int TOTAL_CHARS = 0;

bool wspace(int c) {
  return (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32);
}

void wc(char* filename) {
  int words = 0;
  int lines = 0;
  int chars = 0;
  FILE* file = fopen(filename, "rt");
  if (file != NULL) {
    int c;
    while ((c = fgetc(file)) != EOF) {
      chars++;
      if (!iswspace(c)) {
        while (!iswspace(c = fgetc(file)) && c != EOF) {
          chars++;
        }
        if (wspace(c)) chars++;
        words++;
      }
      if (c == '\n')
        lines++;
    }
    fclose(file);
    if (L) printf("      %d", lines);
    if (W) printf("      %d", words - WORDS_EXCLUDED);
    if (C) printf("      %d", chars - CHARS_EXCLUDED);

    TOTAL_WORDS += (words - WORDS_EXCLUDED);
    TOTAL_LINES += lines;
    TOTAL_CHARS += (chars - CHARS_EXCLUDED);

    WORDS_EXCLUDED = CHARS_EXCLUDED = 0;
  }
  else {
    exit(EXIT_FAILURE);
  }
}

void exclude_comments(char* filename) {
  FILE* file = fopen(filename, "rb");
  if (file != NULL) {
    int c1;
    int c2;
    while ((c1 = fgetc(file)) != EOF) {
      if (c1 == '/' && c2 == '/') {
        CHARS_EXCLUDED += 2;
        int c;
        while((c = fgetc(file)) != '\n' && c != EOF) {
          CHARS_EXCLUDED++;
        }
        c1 = c;
      }
      c2 = c1;
    }
    fclose(file);
  }
  else {
    exit(EXIT_FAILURE);
  }
  
  file = fopen(filename, "rb");
  if (file != NULL) {
    int c; 
    while ((c = fgetc(file)) != EOF) {
      if (!wspace(c)) {
        int c1 = c;
        int c2;
        bool no_space_before_comment = false;
        if (c1 != '/') {
          no_space_before_comment = true;;
        } 
        while (!wspace(c1) && c1 != EOF) {
          if (c1 == '/' && c2 == '/') {
            int c3;
            int c4 = c1;
            while ((c3 = fgetc(file)) != '\n' && c3 != EOF) {
              if (!wspace(c4) && wspace(c3)) WORDS_EXCLUDED++;
              c4 = c3;
            }
            if (!wspace(c4)) WORDS_EXCLUDED++;
            if(no_space_before_comment) WORDS_EXCLUDED--;
            c1 = c3;
          }
          else {
            c2 = c1;
            c1 = fgetc(file);
          }
        }
      }
    }
    fclose(file);
  }
  else {
    exit(EXIT_FAILURE);
  }

}

int main(int argc, char* argv[], char* env[]) {
  int i;
  if (argc == 1 || (argc > 1 && (argv[1][0] != '-' || strcmp(argv[1], "-C") == 0))) W = L = C = true;
  bool ellide_comments = false;
  int numfiles = 0;
  for (i = 1; i < argc; i++) {
    int j;
    char* arg = argv[i];
    if (arg[0] == '-') {
      for (j = 1; j < strlen(arg); j++) {
        if (arg[j] == 'C') ellide_comments = true;
        else if (arg[j] == 'w') W = true;
        else if (arg[j] == 'l') L = true;
        else if (arg[j] == 'c') C = true;
      }
    } else {
      numfiles++;
      if (ellide_comments) exclude_comments(arg);
      wc(arg);
      printf(" %s\n", arg);
    }
  }

  if (numfiles > 1) printf("      %d      %d      %d total\n", TOTAL_LINES, TOTAL_WORDS, TOTAL_CHARS);

  if (numfiles == 0) {
    char* filename = "temp.txt";
    FILE* file = fopen(filename, "wb");
    // Some of the code below is taken from stackoverflow, credit to user: user411313
    char *text = calloc(1,1), buffer[10];
    while(fgets(buffer, 10 , stdin)) {
      text = realloc( text, strlen(text)+1+strlen(buffer) );
      if(!text){} 
      strcat( text, buffer ); 
    }
    fprintf(file, "%s", text);
    fclose(file);
    
    if (ellide_comments) exclude_comments(filename);
    wc(filename);
    printf("\n");

    remove(filename);
  }
  exit(0);
}
