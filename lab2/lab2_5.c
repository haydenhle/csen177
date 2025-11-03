//Name: Hayden Le
//Date: 1/14/25
//Title: Lab2 step 5
//Description: create 7 processes including itself
//Balanced tree: parent --> child 1
//                                  --> grandchild 1
//                                  --> grandchild 2
//                      --> child 2
//                                  --> grandchild 3
//                                  --> grandchild 4

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* wait */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

int main() {
	pid_t pid;
	printf("\n Before forking.\n");
	printf("parent pid: %d\n", getpid());

	// child
	if (fork() == 0)
	{
	
		//granchild
		if (fork() == 0)
		{
		
		}
		else 
		{
			// grandchild
			if (fork() == 0) 
			{
				
			}
			else
			{
				
			}
			
		}
		
	}
	// parent
	else
	{
		// child
		if(fork() == 0) 
		{
		
			// grandchild
			if(fork() == 0) 
			{
				
			}
			else
			{
				if (fork() == 0)
				{
					// grandchild
					
				}
				else
				{
				}
			}
		}
		else
		{
		}
	}
	printf("child pid: %d from parent pid: %d with children: %d,%d\n", getpid(), getppid(), wait(NULL), wait(NULL));
	return 0;
}
