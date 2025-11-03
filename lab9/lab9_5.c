#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

char inputf[20];
int buffersize; 

// thread
void *go(void *arg) 
{ 
	char buffer[buffersize]; 
	FILE *fp;
	FILE *fpout;
    // output
	char fout[20];

    // append thread number to the name of the output file
	sprintf(fout, "output%d.txt", (int)arg);
	fp = fopen(inputf, "rb");
	fpout = fopen(fout, "wb");
    
    // read
	while (fread(buffer, sizeof(buffer), 1, fp)) 
    { 
        // write
		fwrite(buffer, sizeof(buffer), 1, fpout); 
	}
	fclose(fp);
	fclose(fpout);
	return NULL;
}

int main(int argc, char *argv[]) 
{
	int i;
	int NTHREADS = atoi(argv[3]);
	pthread_t threads[NTHREADS];

	strcpy(inputf, argv[1]); 
	buffersize = atoi(argv[2]);

    // create threads
	for(i = 0; i < NTHREADS; i++) 
	{
		pthread_create(&threads[i], NULL, go, (void*)(size_t)i);
	}
    // close threads
	for(i = 0; i < NTHREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}	
	return 0;
}