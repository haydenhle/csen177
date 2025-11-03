//Name: Hayden Le
//Date: 1/14/25
//Title: Lab2 step 6
//Description: step 1 but with threads

#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <pthread.h> /* threads */

void* threadOne(void *x) 
{
	int y = *((int *) x);
	for(int z = 0; z < 100; z++) 
	{
		printf("Thread 1: %d \n", z);
		usleep(y);
	}
	return 0;
}

void* threadTwo(void *x) 
{
	int y = *((int *) x);
	for(int z = 0; z < 100; z++) 
	{
 		printf("Thread 2: %d \n\n", z);
		usleep(y);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	// delay in micro sec
	int n = atoi(argv[1]);
	int *x = malloc(sizeof(*x));
	*x = n;

	pthread_t thread1;
	pthread_t thread2;
	
	pthread_create(&thread1, NULL, threadOne, x);
	pthread_create(&thread2, NULL, threadTwo, x);

	pthread_join(thread1, NULL); 
	pthread_join(thread2, NULL); 
	return 0;
}
