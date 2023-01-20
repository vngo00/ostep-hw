#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sched.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s iterations\n", argv[0]);
		exit(1);
	}

	int iter = atoi(argv[1]);
	struct timeval start, end;
	gettimeofday(&start, NULL);
	for(int i =0 ; i < iter; i++){
		if (read(0, NULL,0) < 0) {
			fprintf(stderr, "read");
			exit(1);
		}
	}
	gettimeofday(&end, NULL);
	
	printf("time = %ld\n", (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	/* measuring context swithc */
	cpu_set_t set;
	CPU_ZERO(&set);
	CPU_SET(0, &set);
	int fd[2], fd1[2];
	if (pipe(fd) < 0 || pipe(fd1) < 0) {
		fprintf(stderr, "pipe");
		exit(1);
	}
	gettimeofday(&start, NULL);
	pid_t cp = fork();
	if (cp < 0) {
		fprintf(stderr, "fork");
		exit(1);
	}
	if (cp == 0) {
		// child process
		if (sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
			fprintf(stderr, "sche_setaffinity");
			exit(1);
		}
		close(fd[0]);
		close(fd1[1]);
		for(int i = 0; i < iter; i++){
			write(fd[1], NULL, 0);
			read(fd1[0], NULL, 0);
		}
	} else {
		if (sched_setaffinity(getpid(), sizeof(set), &set) < 0) {
			fprintf(stderr, "sche_setaffinity");
			exit(1);
		}
		close(fd[1]);
		close(fd1[0]);
		for(int i =0 ; i < iter; i++){
			read(fd[0], NULL, 0);
			write(fd1[1], NULL, 0);
		}


	}
		gettimeofday(&end, NULL);
	printf("context switch time = %ld\n", (end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	return 0;
}
