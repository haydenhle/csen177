#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buffer[atoi(argv[2])]; 
	FILE *fp;
    // open file specified by argv[1]
	fp = fopen(argv[1], "rb"); 
	FILE *fpout;
    // output
	fpout = fopen("output.txt", "wb"); 
    // read
	while (fread(buffer, sizeof(buffer), 1, fp))
    { 
        // write
		fwrite(buffer, sizeof(buffer), 1, fpout); 
	}
	fclose(fp);
	fclose(fpout);
	return 0;
}