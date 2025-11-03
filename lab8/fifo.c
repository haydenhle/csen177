//Name: Hayden Le
//Date: 2/25/25
//Title: Lab8 – First In First Out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int cacheIndex = 0;

    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0;

    int page_num;
    
    for (int i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	page_num = atoi(pageCache); // Stores number read from file as an int
        totalRequests++;

        // loop through array
        for (int i = 0; i < CACHE_SIZE; i++)
        {
            // if item found in array, skip
            if (cache[i].pageno == page_num)
            {
                break;
            }
            // if not found
            if (i == CACHE_SIZE-1)
            {
                printf("Page %d error\n", page_num);
                // increment fault
                totalFaults++;
                // put number in array
                cache[cacheIndex].pageno = page_num;
                // increment index
                cacheIndex = (cacheIndex+1) % CACHE_SIZE;
            }
        }
    }
    double hits = (totalRequests - totalFaults) / (double)totalRequests;
    fprintf(stderr, "%d Total Page Faults in %d Page Requests", totalFaults, totalRequests);
    fprintf(stderr, "FIFO Hitrate = %f\n", hits);
    return 0;
}
