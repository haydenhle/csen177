//Name: Hayden Le
//Date: 1/21/25
//Title: Lab3 step 4
//Description: cat /etc/passwd | grep root shell command

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// main
int main()
{
	int fds[2];
	pipe(fds);

	// child 1 dupe downstream
	if (fork() == 0)
	{
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("grep", "grep", "root", 0);
	}

	// child 2 dupe upstream
	else if (fork() == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", 0);
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
