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

int matchhere(char *regexp, char *text, char *matching);
int matchstar(int c, char *regexp, char *text, char* matching);

int regmatch(char *regexp, char *text, char *matchedtext) {
  char matching[1000];
	memset(matching, 0, sizeof(matching));
	do {
		if(matchhere(regexp, text, matching)) {
						strcpy(matchedtext, matching);
						//printf("Matching text: %s\n", matching);
						return 1;
		}
	} while(*(text++)!='\0');
	return 0;
}

int matchhere(char* regexp, char *text, char *matching) {
	if(regexp[0]=='\0') return 1;
	if(regexp[1]=='*') return matchstar(regexp[0], regexp+2, text, matching);
	if(*text!='\0' && regexp[0]==*text) {strncat(matching, text, 1); return matchhere(regexp+1, text+1, matching);}
	return 0;
}

int matchstar(int c, char *regexp, char *text, char *matching) {
	do {
		if(matchhere(regexp, text, matching)) return 1;
		//if(regexp[1]!='*' || regexp[2]=='\0')
		else if(*text!='\0' && *text==c)	strncat(matching, text, 1);
	} while(*text!='\0' && *text++==c);
	return 0;
}

int regmatch_main(int argc, char **argv){
 /* int match = regmatch(argv[1], argv[2]);
	if(match) {
		printf("Matched Pattern: %s Line: %s\n", argv[1], argv[2]);
	}
	else printf("Not matched pattern: %s Line: %s\n", argv[1], argv[2]);
 */	return 0;
}
