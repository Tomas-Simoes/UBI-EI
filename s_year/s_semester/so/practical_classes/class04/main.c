#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "so2025.h"

int main(int argc, char *argv[])
{
    clock_t startTime, endTime;
    float timeUsed;

    char *fileName = argv[1];
    int blocksize = atoi(argv[2]);

    if (argc < 3)
    {
        perror("Invalid parameters. Excepted fileName and blocksize.\n");
        return 0;
    }

    // printf("Opening file %s with blocksize %d\n", fileName, blocksize);

    startTime = clock();
    double d = whiteSpacePercent(fileName, blocksize);
    endTime = clock();

    timeUsed = (float)(endTime - startTime) / (float)CLOCKS_PER_SEC;

    // printf("\n(Operation done in %f s)  Got %.2f%% of whitespaces.\n", timeUsed, d);
}