// Name: Hayden Le
// Date: 2/4/25
// Title: Lab5-Step3
// Desc: Producer Consumer with semaphores

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>

#define NTHREADS 10
#define n 10
pthread_t threads[NTHREADS];

sem_t *mutex; // 1
sem_t *empty; // n, if 0 then buffer full
sem_t *full; // 0, if 0 then buffer empty

int Buffer[n];

int x;
int y;

// run producer infinitely
void *producer(void* arg)
{
	do
	{
		// make rand items
		int item = rand() % 10;
		sleep(1);
		printf("%d ", (int)arg);

		// wait til consumer empties
		sem_wait(empty);
		// critical section start
		sem_wait(mutex);

		// fill with items
		Buffer[x] = item;
		// increment index
		x = (x+1) % n;

		// end critical section
		sem_post(mutex);
		sem_post(full);
		printf("Produced item: %d\n", item);
	} while(1);
}

// run consumer infinitely
void *consumer(void* arg)
{
	do
	{
		sem_wait(full);
		sem_wait(mutex);

		int item = Buffer[y];
		y = (y+1) % n;

		// end critical section
		sem_post(mutex);
		sem_post(empty);
		sleep(1);

		printf("Consuming item: %d\n", item); 
	} while(1);
}

int main()
{
	// refresh
	x = 0;
	y = 0;

	// create semaphores
	// O_CREAT: create if doesn't exist
	// 0644: standard perms
	mutex = sem_open("Mutex", O_CREAT, 0644, 1);
	empty = sem_open("Empty", O_CREAT, 0644, n);
	full = sem_open("Full", O_CREAT, 0644, 0);

	// create producers
	for (int i = 0; i < NTHREADS/2; i++)
	{
		pthread_create(&threads[i], NULL, producer, (void *)(size_t)i);
	}

	// create consumers
	for (int i = NTHREADS/2; i < NTHREADS; i++)
	{
		pthread_create(&threads[i], NULL, consumer, (void *)(size_t)i);
	}

	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	sem_unlink("Mutex");
	sem_unlink("Empty");
	sem_unlink("Full");

	return 0;
}
