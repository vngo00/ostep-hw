#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main()
{
		

	int cp = fork();
	if (cp < 0){
		fprintf(stderr, "fork");
		exit(1);
	}
	
	if (cp == 0){
		// child process
		printf("hello\n");
	}
	else {
		for(unsigned int i=0; i < 100000000; i++);
		printf("goodbye");
	}
	return 0;
}
		// parent process
