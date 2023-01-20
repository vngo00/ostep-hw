#include <stdio.h>
#include <unistd.h> //exit
#include <stdlib.h> // fork
#include <sys/wait.h> // waitpid


int main() 
{
	int wstatus;
	int wstatus1;
	pid_t cp = fork();
	if (cp < 0) {
		fprintf(stderr, "fork");
		exit(1);
	}
	if (cp == 0) { //child process
		printf("child doing something\n");
		int wait_cp = waitpid(-1, &wstatus1, WUNTRACED | WCONTINUED);
		printf("wait_cp in child: %d\n", wait_cp);

		printf("value of wstatus1: %d\n", wstatus1);

		printf("terminated normally?: %d\n", WIFEXITED(wstatus1));
		printf("terminated normally?: %d\n", WEXITSTATUS(wstatus1));
		
	} else {
		int wait_cp1 = waitpid(cp, &wstatus, WUNTRACED | WCONTINUED);
		printf("wait_cp in parent: %d\n", wait_cp1);
		printf("terminated normally?: %d\n", WIFEXITED(wstatus));
	}
	return 0;
}

