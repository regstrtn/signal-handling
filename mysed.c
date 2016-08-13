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

/******************************************************************
 * Filename: 
 * Created by: Mohammad Luqman
 *
 *
 * ****************************************************************/

int deletelines(FILE *fp, char *args) {
	char *buffer = NULL;
  size_t bufsize=0;
	int charsread = 0;
	int i = 1;
	int j = 0, k = 0;
	int linenum[100];
	char **endptr;
	int commaflag = 0, periodflag = 0;
	char c;
	int arglen = strlen(args);
	printf("Args: ");
	while(j<arglen) {
		if(args[j]==',') commaflag = j;
		if(args[j]=='.') periodflag = j;
		j++;
	}
	printf("Commaflag: %d Periodflag: %d\n", commaflag, periodflag);
	if(!commaflag && !periodflag) { //only single line needs to be deleted
			linenum[0] = atoi(args+1); 
			printf("%s, %d, %s, \n", args+1, 2*linenum[0], args+3);
			//deletesingleline(fp, linenum[0]);
	}
	
	if(periodflag) { //Delete a block of lines
			linenum[0] = atoi(args+i);
			linenum[1] = atoi(args+periodflag+1);
			printf("%s, %d, %d, \n", args+1, 2*linenum[0], 2*linenum[1]);
			//deleteblock(fp, linenum[0], linenum[1]);
	}
	j = 0; k = 1; //Start k from 1 because 1st linenum is filled manually
	
	if(commaflag) {
		linenum[0] = atoi(args+1);
		while(j<=commaflag) {
			printf("While loop: %d \n", j);
			if(args[j]==','){
							linenum[k] = atoi(args+j+1);
							printf("%d ", linenum[k]);
							k++;
						}
			j++;
		}
		linenum[j] = 1000000;
	}
	printf("\n");
	while((charsread = getline(&buffer, &bufsize, fp))>0) {
		printf("%d %s", i, buffer);
		i++;
	}
	return 0;
}


int main(int argc, char **argv){
		FILE *fp = fopen("sm.txt", "r+");
		deletelines(fp, argv[1]);
			return 0;
}

