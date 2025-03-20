/* ex71.c : compilar cc -Wall -c ex71.c -o ex71 */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "so2025.h"

double whiteSpacePercent(char *fileName, int blockSize)
{
    int file = open(fileName, O_RDONLY);
    int n;

    if (file == -1)
    {
        perror("opening file");
    }

    char *buffer = malloc(blockSize);
    int characterCount = 0;

    int whiteSpaceCount = 0;

    while ((n = read(file, buffer, blockSize)) > 0)
    {
        if (n == -1)
        {
            perror("reading file");
        }

        characterCount += n;
        for (int i = 0; i < n; i++)
        {
            if (buffer[i] == ' ')
            {
                whiteSpaceCount++;
            }
        }
    }

    free(buffer);
    close(file);

    // printf("Got %d whitespaces from %d characters.\n", whiteSpaceCount, n);

    return ((double)whiteSpaceCount / characterCount) * 100;
}