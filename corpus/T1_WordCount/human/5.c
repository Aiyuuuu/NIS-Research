#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *pgmname;
char *filename;
short cflag = 0;
short lflag = 0;
short wflag = 0;
int totals[4] = {};
FILE *fp;

// stats printing function
void printCounts(int inc);

void main(int argc, char *argv[]) {
   int c, i;
   char *cp;

   // get program name
   pgmname = argv[0];

   // set file pointer to standard input
   fp = stdin;

   // step through arguments (if any)
   for(i = 1; i < argc; i++) {
      cp = argv[i];
      // if arg string starts with '-', it's a flag
      if(*cp == '-') {
         // step through chars of current flag string, set flags
         while(*cp != '\0') {
            *++cp;
            if(*cp == 'c')
               ++cflag;
            else if (*cp == 'l')
               ++lflag;
            else if (*cp == 'w')
               ++wflag;
            // if end of arg string, continue
            else if (*cp == '\0')
               continue;
            // default: not a valid flag char, exit with error
            else {
               fprintf(stderr, "%s: Invalid option -- '-'\n", pgmname);
               exit(1);
            }
         }
      }
      // arg string NOT a flag, treat as a filename, try to open file
      else {
         fp = fopen (cp,"r");
         // not a valid filename, print error and continue
         if(fp == NULL) {
            fprintf(stderr, "%s: %s: No such file or directory\n", pgmname, cp);
            continue;
         }
         // if we've opened a file, get filename, print file stats
         if(fp != stdin) {
            filename = cp;
            printCounts(c);
         }
      }
   }
   //  no arguments found, take stdin, set filename NULL, print file stats
   if(fp == stdin) {
      filename = NULL;
      printCounts(c);
   }
   // if multiple files, print total stats
   if(totals[0] >1) {
      //printf("%10s%10s%10s \n\n", "lines", "words", "chars");
      printf("%10d%10d%10d total \n", totals[1], totals[2], totals[3]);
   }
}

void printCounts(int c) {
   int char_cnt = 0, nl_cnt = 0, word_cnt = 0;
   short word_flag = 0;
   // for current file or input stream, pull chars until end of file
   while((c = getc(fp)) != EOF) {
      // count line
      if(c == '\n')
         ++nl_cnt;
      // count char
      ++char_cnt;
      // if word start, flag start, count word
      if(word_flag != 1 && !isspace(c)) {
         word_flag = 1;
         ++word_cnt;
      }
      // else word end, clear flag
      else if(word_flag == 1 && isspace(c))
         word_flag = 0;
   }

   // increment totals array ([0] = files, [1] = lines, [2] = words, [3] = chars)
   ++totals[0];
   totals[1] += nl_cnt;
   totals[2] += word_cnt;
   totals[3] += char_cnt;
   
   // trap for flag options and display appropriate columns
   if((cflag && lflag && wflag) || !cflag && !lflag && !wflag) {
      //printf("%10s%10s%10s%10s \n\n", "lines", "words", "chars", "filename");
      printf("%10d%10d%10d%10s \n", nl_cnt, word_cnt, char_cnt, filename);
   }
   else if(cflag && lflag) {
      //printf("%10s%10s%10s \n\n", "lines", "chars", "filename");
      printf("%10d%10d%10s \n", nl_cnt, char_cnt, filename);
   }
   else if(cflag && wflag) {
      //printf("%10s%10s%10s \n\n", "words", "chars", "filename");
      printf("%10d%10d%10s \n", word_cnt, char_cnt, filename);
   }
   else if(lflag && wflag) {
      //printf("%10s%10s%10s \n\n", "lines", "words", "filename");
      printf("%10d%10d%10s \n", nl_cnt, word_cnt, filename);
   }
   else if(cflag) {
      //printf("%10s%10s \n\n", "chars", "filename");
      printf("%10d%10s \n", char_cnt, filename);
   }
   else if(lflag) {
      //printf("%10s%10s \n\n", "lines", "filename");
      printf("%10d%10s \n", nl_cnt, filename);
   }
   else if(wflag) {
      //printf("%10s%10s \n\n", "words", "filename");
      printf("%10d%10s \n", word_cnt, filename);
   }
}


