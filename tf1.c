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
 * Filename: 
 * Created by: Mohammad Luqman
 *
 *
 * ****************************************************************/

void modifystr(char *str) {
	str = (char*)malloc(100*sizeof(char));
	strcpy(str, "dafuq");
}

int main(int argc, char **argv){
  char *str;
	modifystr(str);
	printf("%s\n", str);
	return 0;
}
