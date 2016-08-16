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
//#include "deletelines.c"
#include "regmatch.c"
#define MAXNUMTOKENS 10


/******************************************************************
 * Filename: mysed.c 
 * Created by: Mohammad Luqman
 * 1. Match and replace text
 * 2. Delete lines specified by line numbers
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

int replacepattern(FILE *fp, char* args) {
	char **tokens;
	tokens = split_into_tokens(args);
	printf("Tokens split received: %s %s %s\n", tokens[0], tokens[1], tokens[2]);
	printf("Match result: %d\n", regmatch(tokens[1], tokens[2]));
	return 0;
}


int main(int argc, char **argv){
		FILE *fp = fopen("sm.txt", "r+");
		char flagchar;
		int argvlen = strlen(argv[1]);
		flagchar = argv[1][argvlen-1];
		printf("Flagchar: %c", flagchar);
		//deletelines(fp, argv[1]);
		replacepattern(fp, argv[1]);
		return 0;
}

