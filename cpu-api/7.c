#include <stdio.h>
#include <stdlib.h> //exit
#include <sys/wait.h>
#include <unistd.h> //close

int main()
{
	int cp = fork();
	if (cp < 0) {
		fprintf(stderr, "fork");
		exit(1);
	}
	if (cp == 0) {
		close(STDOUT_FILENO);
		printf("child here\n");
	} else {
		wait(NULL);
		printf("parent here\n");
	}
	return 0;
}

