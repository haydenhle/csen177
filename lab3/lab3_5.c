//Name: Hayden Le
//Date: 1/21/25
//Title: Lab3 step 5
//Description: producer-consumer

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// main
int main(int argc, char *argv[])
{
	int fds[2];
	pipe(fds);
	
	char buffer[100];
	int count;
	int i;

	// child 1 producer
	if (fork() == 0)
	{
		printf("Enter Producer message:\n");
		close(fds[0]);
		char input[100];
		while (1)
		{
			scanf("%s", input);
			write(fds[1], input, strlen(input));
		}
		exit(0);
	}

	// child 2 consumer
	else if (fork() == 0)
	{
		close(fds[1]);	
		while ((count = read(fds[0], buffer, 100)) > 0)
		{
			printf("Consumer message:\n");
			printf("%s\n", buffer);
		}
		exit(0);
	}

	// parent closes and waits for children
	else
	{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
