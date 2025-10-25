
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>



long charsNumber = 0;
long wordsNumber = 0;
long linesNumber = 0;
int exitCode = 0;
int flags = 0;

void fileCount(char* fileName);
void stdinCount();
void printSum(char source[], long lines,long words, long characters);

#define l_Flag 0x01 // 0b0000 0000 0000 0001
#define w_Flag 0x02 // 0b0000 0000 0000 0010
#define c_Flag 0x04 // 0b0000 0000 0000 0100

#define BRED "\e[1;31m"
#define reset "\e[0m"


int main(int argc,char*argv[]) {

	
	int i = 1;

	if(argc == 1) {
		stdinCount();
		printSum("Total :",linesNumber,wordsNumber, charsNumber);
		return exitCode;
	} else {

		if( (*(argv[1] + 0) == '-') ) {

			while( (i <= argc - 1) && (*(argv[i] + 0) == '-') ) {
			
				if(strcmp(argv[i],"-l") == 0) {
					flags = flags | l_Flag;
				} else if(strcmp(argv[i],"-w") == 0) {
					flags = flags | w_Flag;
				} else if(strcmp(argv[i],"-c") == 0) {
					flags = flags | c_Flag;
				} else {
					fprintf(stderr, BRED "Error :" reset " Unknown Flag <%s>\n",argv[i]);
					exit(2);
				}
				
				i++;
			}
		
			if(i == argc) {
				stdinCount();
				printSum("Total :",linesNumber,wordsNumber, charsNumber);
				return exitCode;
			} 
			
		}
		
		
		while((i <= argc - 1)) {
			if(strcmp(argv[i],"+") == 0) {
				stdinCount();
			} else {
				fileCount(argv[i]);
			}
		
			i++;
		}

		printSum("Total :",linesNumber,wordsNumber, charsNumber);
	}

	return 0;
}

void printSum(char source[], long lines,long words, long characters) {
	char result[strlen(source) + 1];
	char lineStr[50],wordStr[50],characterStr[50];

	snprintf(lineStr,50,"%-3ld",lines);
	snprintf(wordStr,50,"%-3ld",words);
	snprintf(characterStr,50,"%-3ld",characters);
	
	
	strcpy(result,source);
	
	printf("%s",result);
	printf("%-*s",(int)(20 - strlen(result)),"");
   	
   if( flags == 0 ) {
   	
   	printf("%-*s",(int)(20 - strlen(lineStr)),lineStr);
   	printf("%-*s",(int)(20 - strlen(wordStr)),wordStr);
   	printf("%s\n",characterStr);

   	
   } else {
   		
	   if((flags & l_Flag) != 0) {
   		printf("%-*s",(int)(20 - strlen(lineStr)),lineStr);
	   }
	    
	   if((flags & w_Flag) != 0) {
	   	printf("%-*s",(int)(20 - strlen(wordStr)),wordStr);
	   }
	   
	   if((flags & c_Flag) != 0) {
	   	printf("%s",characterStr);
	   }
	   
	   printf("\n");
   }
   
   


}

void fileCount(char fileName[]) {
	FILE *fp;
	int ch;
	bool isLetter = false;
	
	long characters = 0,words = 0,lines = 0;

	fp = fopen(fileName,"r");
	
	if(fp == NULL) {
	fprintf(stderr, BRED "Error :" reset " File <%s> can not be opened\n",fileName);
	return;
	}
   
   	while( (ch = fgetc(fp)) != EOF ) {
   		characters++;
   		if(ch == '\n') { lines++;
   			if(isLetter) {
   				words++;
   				isLetter = false;
   			}
   		}
   		else if(ch == ' ') {
   			if(isLetter) {
   				words++;
   				isLetter = false;
   			}
 
   		} else isLetter = true;
   	
   	}
   	
   	/* count last word if file doesn't end with whitespace */
   	if(isLetter) words++;
   	
   	fclose(fp);
   	
   	
   	linesNumber += lines;
   	wordsNumber += words;
   	charsNumber += characters;
   	
	printSum(fileName,lines,words,characters);
}

void stdinCount() {

	int i = 0;
	char *input = "";
	char ch;
	bool isLetter = false;
	long characters = 0,words = 0,lines = 0;
	
	//scanf("%s",&input);

   	while( (ch = fgetc(stdin)) != EOF) {
   		characters++;
   		if(ch == '\n') { lines++;
   			if(isLetter) {
   				words++;
   				isLetter = false;
   			}
   		}
   		else if(ch == ' ') {
   			if(isLetter) {
   				words++;
   				isLetter = false;
   			}
 
   		} else isLetter = true;
   		
   		i++;
   	
   	}
   	
   	/* count last word if stdin doesn't end with whitespace */
   	if(isLetter) words++;
   	
   	linesNumber += lines;
   	wordsNumber += words;
   	charsNumber += characters;	
	
	printSum("-stdin-" ,lines,words,characters);
}


