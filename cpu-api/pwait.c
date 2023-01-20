#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
	int cp = fork();
	
	if (cp < 0){
		fprintf(stderr, "fork");
		exit(1);
	}
	
	if ( cp == 0){
		printf("child doing stuff\n");
	}
	else {
		int w = wait(NULL);
		printf("value of wait: %d", w);
		printf("child ip %d\n", cp);

	}
	return 0;
}

	 
