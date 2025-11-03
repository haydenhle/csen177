//Name: Hayden Le
//Date: 2/25/25
//Title: Lab8 – Second Chance

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct {//to 
    int pageno;
    int second_chance;
} ref_page;


int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int cacheIndex = 0;

    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0;

    int page_num;
    int count;
    int found;
    
    for (int i = 0; i < CACHE_SIZE; i++){//initialise cache array  
        cache[i].pageno = -1;
        cache[i].second_chance = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	page_num = atoi(pageCache); // Stores number read from file as an int
        totalRequests++;

        // loop through array
        for (int i = 0; i < CACHE_SIZE; i++)
        {
            // if found in array set second_chance = 1
            if (cache[i].pageno == page_num)
            {
                cache[i].second_chance = 1;
                found = 0;
                break;
            }
            if (i == CACHE_SIZE-1)
            {
                found = 1;
            }
        }

        // if not found
        if (found)
        {
            printf("Page %d caused a fault\n", page_num);
            totalFaults++;
            
            // iterate through 
            while (1)
            {
                // set second chance back to 0 
                if (cache[count].second_chance == 1)
                {
                    cache[count].second_chance = 0;
                    count = (count + 1) % CACHE_SIZE;
                }
                
                // insert page num
                else
                {
                    cache[count].pageno = page_num;
                    cache[count].second_chance = 0;
                    count = (count + 1) % CACHE_SIZE;
                    break;
                }
            }
        }
    }
    double hits = (totalRequests - totalFaults) / (double)totalRequests;
    fprintf(stderr, "%d Total Page Faults in %d Page Requests", totalFaults, totalRequests);
    fprintf(stderr, "Second Chance Hitrate = %f\n", hits);
    return 0;
}
