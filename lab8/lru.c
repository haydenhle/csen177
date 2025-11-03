//Name: Hayden Le
//Date: 2/25/25
//Title: Lab8 – Least Recently Used

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int age;
} ref_page;


int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int cacheIndex = 0;

    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0;

    int i;
    int page_num;
    int oldest;
    
    for (int i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         cache[i].age = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	page_num = atoi(pageCache); // Stores number read from file as an int
        totalRequests++;
        oldest = cache[0].age;

        // loop through array
        for (int i = 0; i < CACHE_SIZE; i++)
        {
            // if found in array
            if (cache[i].pageno == page_num)
            {
                for (int j = 0; j < CACHE_SIZE; j++)
                {
                    cache[j].age++;
                    /*
                    // increment age for all younger
                    if (cache[j].age < cache[i].age)
                    {
                        cache[j].age++;
                    }
                    */
                }
                // reset age after hit
                cache[i].age = 0;
                break;
            }

            // if array full
            else if (i == CACHE_SIZE-1)
            {
                printf("Page %d caused a fault\n", page_num);
                totalFaults++;
                
                // increase all age
                for (int j = 0; j < CACHE_SIZE; j++)
                {
                    cache[j].age++;
                }

                for (int k = 0; k < CACHE_SIZE; k++)
                {
                    // if older page exists
                    if (oldest < cache[k].age)
                    {
                        oldest = cache[k].age;
                        cacheIndex = k;
                    }
                }
                cache[cacheIndex].pageno = page_num;
                cache[cacheIndex].age = 0;
            }
        }
    }
    double hits = (totalRequests - totalFaults) / (double)totalRequests;
    fprintf(stderr, "%d Total Page Faults in %d Page Requests", totalFaults, totalRequests);
    fprintf(stderr, "LRU Hitrate = %f\n", hits);
    return 0;
}
