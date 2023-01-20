#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void w();
void cfork(int cp);

int main()
{
	printf("pid: %d\n", (int) getpid());
	char* argv[] = {"ls", "-l", "-a", (char *) NULL};
	char* env[] = {(char *) NULL};

	int cp = fork();
	cfork(cp);

	if (cp == 0) {
		// child process
		printf("execl\n");
		execl("/usr/bin/ls", "ls", "-l", "-a", "/tmp/tmp.txt" ,(char *) NULL);
	}
	w();

	cp = fork();
	cfork(cp);
	if (cp == 0) {
		printf("execle\n");
		execle("/usr/bin/ls", "ls", "-la", "/tmp/tmp.txt", (char *) NULL, env);
	}
	w();

	cp = fork();
	cfork(cp);
	if (cp == 0) {
		printf("execlp\n");
		execlp("ls", "ls", "-la", "/tmp/tmp.txt", NULL);
	}
	w();

	cp = fork();
	cfork(cp);
	if (cp == 0) {
		printf("execv\n");
		execv("/usr/bin/ls", argv);
	}
	w();
	
	
	cp = fork();
	cfork(cp);
	if (cp == 0) {
		printf("execvp\n");
		execvp(argv[0], argv);
	}
	w();

	
	cp = fork();
	cfork(cp);
	if (cp == 0) {
		printf("execvpe\n");
		execvpe(argv[0], argv, env);
	}
	w();
	return 0;
}

void w()
{
	if(wait(NULL) < 0) {
		fprintf(stderr, "wait");
		exit(1);
	}
}

void cfork(int cp)
{
	if (cp < 0)
	{
		fprintf(stderr, "fork");
		exit(1);
	}
}
