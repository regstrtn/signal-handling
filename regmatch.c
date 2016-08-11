#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


/******************************************************************
 * Filename: regmatch.c
 * Created by: Mohammad Luqman
 *
 *
 * ****************************************************************/

int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

int regmatch(char *regexp, char *text) {
  do {
		if(matchhere(regexp, text)) return 1;
	} while(*(text++)!='\0');
	return 0;
}

int matchhere(char* regexp, char *text) {
	if(regexp[0]=='\0') return 1;
	if(regexp[1]=='*') return matchstar(regexp[0], regexp+2, text);
	if(*text!='\0' && regexp[0]==*text) return matchhere(regexp+1, text+1);
	return 0;
}

int matchstar(int c, char *regexp, char *text) {
	do {
		if(matchhere(regexp, text)) return 1;
	} while(*text!='\0' && *text++==c);
	return 0;
}

int testmain(int argc, char **argv){
  int match = regmatch(argv[1], argv[2]);
	if(match) {
		printf("Matched Pattern: %s Line: %s\n", argv[1], argv[2]);
	}
	else printf("Not matched pattern: %s Line: %s\n", argv[1], argv[2]);
	return 0;
}
