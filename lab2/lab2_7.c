//Name: Hayden Le
//Date: 1/14/25
//Title: Lab2 step 7
//Description: parent make child that runs ls command

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	printf("\n Before forking.\n");
	pid = fork();
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	
	else if (pid == 0)
	{
		execlp("/bin/ls", "ls", NULL);
	}
	else
	{
		wait(NULL);
		printf("Child Complete");
		exit(0);
	}
}
