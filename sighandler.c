#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <stdlib.h>

/****************************************
 * Filename: sighandler.c
 * Created and owned by: Mohammad Luqman
 *
 * Acknowledgements:
 * ----------------
 *  Geeks for geeks
 *
 *
 * **************************************/

int createtempfile();
void sighandler2(int signo);
void sighandler3(int signo);

int createtempfile() {
	char *s = "Interrupt\n";
	FILE *fp = fopen("temp", "w");
	fprintf(fp,"%s", s);
	return 0;
}

void sig_handler(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGKILL)
        printf("received SIGKILL\n");
    else if (signo == SIGSTOP)
        printf("received SIGSTOP\n");
    else if(signo == SIGINT) 
    	{
    		printf("Ctrl+C received\n");
    		createtempfile();
    		signal(SIGINT, sighandler2);	
			}
    else if(signo == SIGQUIT) {
    	printf("Ctrl+\\ received\n");
    	exit(0);
    	}
}

void sighandler2(int signo) {
	char *s = "Some one is trying to kill me!!\n";
	if(signo == SIGINT) {
		printf("%s", s);
		signal(SIGINT, sighandler3);
		}
}

void sighandler3(int signo) {
	if(signo == SIGINT) {
		  printf("Alright! I am gonna go die now\n");
			exit(0);
		}
}


int main(void)
{
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\nCan't catch SIGUSR1\n");
    if (signal(SIGKILL, sig_handler) == SIG_ERR)
        printf("\nCan't catch SIGKILL\n");
    if (signal(SIGSTOP, sig_handler) == SIG_ERR)
        printf("\nCan't catch SIGSTOP\n");
    signal(SIGQUIT, sig_handler);
    signal(SIGINT, sig_handler);
    // A long long wait so that we can easily issue a signal to this process
    while(1) 
        sleep(1);
    return 0;
}
