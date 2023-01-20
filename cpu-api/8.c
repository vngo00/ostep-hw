#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // pipe, close
#include <sys/wait.h> // wait

int main()
{
	pid_t rc[2];
	int fd[2];
	
	if (pipe(fd) < 0) {
		fprintf(stderr, "pipe");
		exit(1);
	}
	
	rc[0] = fork();
	if (rc[0] < 0) {
		fprintf(stderr, "fork");
		exit(1);
	} else if (rc[0] == 0) { // child process one
		prinf("before chang stdout file descriptor to the pipe in child process 1\n");
		close(fd[0]);
		if (fd[1] != STDOUT_FILENO) {
			if (dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO){
				fprintf(stderr, "dup2 error to stdout");
				exit(1);
			}
			close(fd[1]);
		}
		printf("from child 1\n");
	}
	else {
		char buf[BUFSIZ];
		rc[1] = fork();
		if (rc[1] < 0) {
			fprintf(stderr, "fork");
			exit(1);
		} else if (rc[1] == 0) {
			// child process two
			close(fd[1]); // close write end
			if (fd[0] != STDIN_FILENO) {
				if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
					fprintf(stderr, "dup2 error to stdin");
					exit(1);
				}
			close(fd[0]);
			}
			read(STDIN_FILENO, buf, BUFSIZ);
			printf("from second child %s\n", buf);
		} else {
			if (waitpid(rc[0], NULL, 0) < 0) {
				fprintf(stderr, "wait 0");
				exit(1);
			}
			if (waitpid(rc[1], NULL, 0) < 0) {
				fprintf(stderr, "wait 1");
				exit(1);
			}
			printf("parent here\n");
		}
	}
	return 0;
}

