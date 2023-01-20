#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int fd = open("/tmp/tmp.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	int cp = fork();
	
	if (cp < 0){
		fprintf(stderr, "fork");
		exit(1);
	}
	
	if (cp == 0) {
		//child process
		printf("child process:\n");
		printf("fd is %d\n", fd);
		char *str = "I am a child";
		write(fd, str, strlen(str));
	}
	else {
		// parent process
		printf("parent process\n");
		printf("fd is %d\n", fd);
		char *str ="My child, I am your father";
		write(fd,str,strlen(str));
	}
	return 0;
}

