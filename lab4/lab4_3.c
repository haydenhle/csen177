//Name: Hayden Le
//Date: 1/28/25
//Title: Lab4 – Step 3
//Description: use threads to calculate parallel matrix multiplication

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 255

void *matrixMult(void *);

//create threads for each row
pthread_t threads[SIZE];

//initialize matricies
double matrixA[SIZE][SIZE];
double matrixB[SIZE][SIZE];
double matrixC[SIZE][SIZE];

int main() 
{
	// fill matrixA
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			matrixA[i][j] = rand() % 10;
		}
	}

	// print matrixA
	printf("Matrix A:\n");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%.1f ", matrixA[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	// fill matrixB
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			matrixB[i][j] = rand() % 10;
		}
	}

	// fill matrixC with 0s
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			matrixC[i][j] = 0;
		}
	}

	// print matrixB
	printf("Matrix B:\n");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%.1f ", matrixB[i][j]);
		}
		printf("\n");
	}

    	
	// create threads
	for (int i = 0; i < SIZE; i++)
	{
		pthread_create(&threads[i], NULL, matrixMult, (void *)(size_t)i);
	}

	// join threads
	for (int i = 0; i < SIZE; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Main Thread Done.\n");

	// print matrixC
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%.1f ", matrixC[i][j]);
		}
		printf("\n");
	}
}

void *matrixMult(void *arg) {
	for (int j = 0; j < SIZE; j++)
	{
		for (int k = 0; k < SIZE; k++)
		{
			matrixC[(int)(size_t)arg][j] += matrixA[(int)(size_t)arg][k]*matrixB[k][j];
		}
	}
}

