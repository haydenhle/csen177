// Name: Hayden Le
// Date: 2/4/25
// Title: Lab5-Step4
// Desc: Producer Consumer with mutex lock

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>

#define P 3
#define C 2
#define n 10

pthread_t tidp[P];
pthread_t tidc[C];

int Buffer[n];

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
int p, c, x, y, count;

// run producer infinitely
void *producer(void* arg)
{
	do
	{
		// make rand items
		int item = rand() % 10;
		pthread_mutex_lock(&mutex);
		while (count == n)
		{
			pthread_cond_wait(&empty, &mutex);
		}

		// fill with items
		Buffer[x] = item;
		// increment index
		x = (x+1) % n;
		count++;

		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
		printf("Produced item: %d\n", item);
		sleep(1);
	} while(1);
}

// run consumer infinitely
void *consumer(void* arg)
{
	do
	{
		pthread_mutex_lock(&mutex);

		while (count == 0)
		{
			pthread_cond_wait(&full, &mutex);
		}

		int item = Buffer[y];
		y = (y+1) % n;
		count--;

		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);
		
		printf("Consuming item: %d\n", item); 
		sleep(1);
	} while(1);
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);
	for(p = 0; p < P; p++)
	{
		pthread_create(&tidp[p], NULL, producer, (void*)(size_t)p);
	}
	for(c = 0; c < C; c++)
	{
		pthread_create(&tidc[c], NULL, consumer, (void*)(size_t)c);
	}
	for(p = 0; p < P; p++) 
	{
		pthread_join(tidp[p], NULL);
		printf("Producer thread %d returned\n", p);
	}
	for(c = 0; c < C; c++) 
	{
		pthread_join(tidc[c], NULL);
		printf("Consumer thread %d returned\n", c);
	}
	printf("Main thread finished\n");
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);
	return 0;	
}
