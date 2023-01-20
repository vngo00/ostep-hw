#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int x  = 100;
	printf("x value before fork: %d\n", x);
	int rc = fork();
	if (rc < 0){
		fprintf(stderr, "fork");
		exit(1);
	}
	
	if(rc == 0){
		// child process
		printf("value of x in cp before modifying %d\n", x);
		x = 123;
		printf("in cd after modify %d\n", x);
	} else {
		wait(NULL);
		//parent process
		printf("value of x in parent before modifying %d\n", x);
		x= 200;
		printf("value of x in parent after modifying %d\n", x);
	}
	return 0;
}

		
