#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{

	int cp = fork();
	
	if (cp < 0) {
		fprintf(stderr, "fork");
		exit(1);
	}
	
	if (cp == 0){ //child process
		printf("child process doing stuff\n");
		int wait_cp = wait(NULL);
		printf("wait_cp : %d\n", wait_cp);
	} else {
		printf("parent doing its bussiness\n");
	}
	return 0;
}


