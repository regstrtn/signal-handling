#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>
#include "deletelines.c"
#include "regmatch.c"
#define MAXNUMTOKENS 10


/******************************************************************
 * Filename: mysed.c 
 * Created and owned by: Mohammad Luqman
 * 1. Match and replace text
 * 2. Delete lines specified by line numbers
 * 
 * Copyright:
 * This code is part of lab assignment 4 - mysed. It cannot be copied
 * or distributed without the express permission of the owner. 
 *
 * ****************************************************************/

char** split_into_tokens(char* str) {
	/*This function takes a string as input and outputs tokens as command or parameter*/
	char* pch;
	char* delim = "/";
	int pos = 0;
	char** tokens = (char **)malloc(MAXNUMTOKENS*sizeof(char*));
	pch = strtok(str, delim);
	while(pch!=NULL) {
		tokens[pos] = pch;
		//printf("%s\n", pch);
		pch = strtok(NULL, delim);
		pos++;
	}
	tokens[pos] = NULL;
	return tokens;
}

int replacepattern(FILE *fpr, FILE *fpw, char* args) {
	char **tokens;
	char matchedtext[1000] = {'\0'};
	char *buffer = NULL;
	size_t bufsize = 0;
	int charsread = 0, matchresult = 0, replaceall = 0, replacen = 1, i = 1;
	char * firstmatch, *matchend;
	char extrachar;
	tokens = split_into_tokens(args);
	printf("Tokens split received: %s %s %s\n", tokens[0], tokens[1], tokens[2]);
	if(tokens[3]!=NULL) {
		if(tokens[3][0] == 'g') replaceall = 1;
		else {replacen = atoi(tokens[3]); printf("replacen: %d\n", replacen);}
	}
	while((charsread = getline(&buffer, &bufsize, fpr))>0) {
		buffer[charsread-1] = '\0';
		i = 1;
		while((replaceall || i<=replacen) && buffer!=NULL) {
			matchresult = regmatch(tokens[1], buffer, matchedtext);
			if(!matchresult) {printf("Not matched\n"); break;}
			firstmatch = strstr(buffer, matchedtext); 
			printf("Matched text: %s Firstmatch: %s", matchedtext, firstmatch);
			matchend = firstmatch+strlen(matchedtext);
			if(replaceall || (!replaceall && i==replacen)) {
				*firstmatch = '\0';
				fprintf(fpw, "%s%s", buffer, tokens[2]);
			}
			if(!replaceall && i!=replacen) {
				extrachar = *(firstmatch+strlen(matchedtext)-1);
				*(firstmatch+strlen(matchedtext)-1)='\0';
				fprintf(fpw, "%s%c", buffer, extrachar);
				//if(matchresult && i!=replacen) fprintf(fpw, "%s",  matchedtext);
			}
			if(matchend!=NULL) buffer = matchend;
			printf("Buffer: %s I: %d\n", buffer, i);
			i++; fflush(NULL);
		}
		if(!matchresult) {fprintf(fpw, "%s\n", buffer);}
	  if(matchresult) fprintf(fpw, "%s\n", matchend);	
		buffer = NULL;
	}
	return 0;
}


int main(int argc, char **argv){
		FILE *fpr;
		if(argv[2]!=NULL) fpr = fopen(argv[2], "r+");
		else fpr = stdin;
		FILE *fpw = fopen("mt2.txt", "w+");
		char deletechar, replacechar;
		int deleteflag = 0, replaceflag = 0;
		int argvlen = strlen(argv[1]);
		deletechar = argv[1][argvlen-1];
		replacechar = argv[1][0];
		printf("Flagchars: %c %c", deletechar, replacechar);
		if(deletechar == 'd') deletelines(fpr,fpw, argv[1]);      //If command ends with d, call delete function
		if(replacechar == 's') replacepattern(fpr, fpw, argv[1]); //If command begins with s, call replace function
		printf("Main returned after calling deletechar and replacechar : %d %d with parameters: %s\n", deletechar, replacechar, argv[2]);
		//remove(argv[2]); rename("mt2.txt", argv[2]);   //Uncomment this before final submission. This will rename new file and delete old file. 
		return 0;
}

