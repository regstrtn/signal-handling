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
 * Filename: deletelines.c 
 * Created by: Mohammad Luqman
 * 1. Match and replace text
 * 2. Delete lines specified by line numbers
 *
 * ****************************************************************/


int findlineinarr(int l, int linenum[], int numcommas) {
	int i=0;
	int flag = 0;
	for(i=0;i<=numcommas;i++) {
		if(l==linenum[i]) flag = 1;
	}
	return flag;
}

int deletelines(FILE *fp,FILE *fpw, char *args2) {
	char *buffer = NULL;
  size_t bufsize=0;
	int charsread = 0;
	int i = 1;
	int invflag = 0;
	int j = 0, k = 0, l = 0, numcommas = 0;
	int linenum[100];
	char **endptr;
	int commaflag = 0, periodflag = 0;
	char c;
	int arglen = strlen(args2);
	char args1[strlen(args2)];
	char args[strlen(args2)];
	if((int)args2[0]=='\\') {
		invflag = 1;
		printf("Invert flag: %d %s\n", invflag, args2);
		strcpy(args1, args2);
		strcpy(args, args1+1);
	}
	else {
		strcpy(args, args2);
	}
	printf("Args1: %s", args);
	while(j<arglen) {
		if(args[j]==',') {commaflag = j; numcommas++;}
		if(args[j]=='.') periodflag = j;
		j++;
	}
	if(!commaflag && !periodflag) { //only single line needs to be deleted
			linenum[0] = atoi(args+1); 
			//printf("%s, %d, %s, \n", args+1, 2*linenum[0], args+3);
			//deletesingleline(fp, linenum[0]);
	l = 1;
		while((charsread = getline(&buffer, &bufsize, fp))>0) {
			if(l!=linenum[0] && !invflag) fprintf(fpw, "%d %s",l, buffer);
			if(l==linenum[0] && invflag) fprintf(fpw, "%d %s", l, buffer);
			l++;
		} 
	} buffer = NULL;	
	if(periodflag) { //Delete a block of lines
			linenum[0] = atoi(args+i);
			linenum[1] = atoi(args+periodflag+1);
			//deleteblock(fp, linenum[0], linenum[1]);
	l = 1;
		while((charsread=getline(&buffer, &bufsize, fp))>0) {
			if(!invflag && (l<linenum[0] || l>linenum[1])) fprintf(fpw, "%d %s",l, buffer);
			if(invflag && (l>=linenum[0] && l<=linenum[1])) fprintf(fpw, "%d %s", l, buffer);
			l++;
			//Code for deleting block of lines here
		}
	}

	j = 0; k = 1; //Start k from 1 because 1st linenum is filled manually
  
	if(commaflag) {
		linenum[0] = atoi(args+1);
		while(j<=commaflag) {
			if(args[j]==','){
							linenum[k] = atoi(args+j+1);
							printf("%d ", linenum[k]);
							k++;
						}
			j++;
		}
		l = 1;
		while((charsread = getline(&buffer, &bufsize, fp))>0) {
			if(!invflag && !findlineinarr(l, linenum, numcommas)) fprintf(fpw, "%d %s", l, buffer);
			if(invflag && findlineinarr(l, linenum, numcommas)) fprintf(fpw, "%d %s", l, buffer);
			l++;
				//match linenum with linenums in array
				//do not print matching line numbers
		}
	}
	/*printf("\n");
	while((charsread = getline(&buffer, &bufsize, fp))>0) {
		printf("%d %s", i, buffer);
		i++;
	}*/
	return 0;
}


int deletelines_main(int argc, char **argv){
		FILE *fp = fopen("sm.txt", "r+");
		FILE *fpw = fopen("mt2.txt", "w+");
		deletelines(fp, fpw, argv[1]);
			return 0;
}

