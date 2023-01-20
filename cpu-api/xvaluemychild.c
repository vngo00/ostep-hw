#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int x  = 100;
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
		//parent process
		printf("value of x in parent before modifying %d\n", x);
		x= 200;
		printf("value of x in parent after modifying %d\n", x);
	}
	return 0;
}

		
