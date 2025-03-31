/* ex72.c : compilar cc -Wall -c ex72.c -o ex72 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int BUFFSIZE;

void ioCopy(int IN, int OUT);

int main(int argc, char *argv[])
{
    int fdIn = open(argv[1], O_RDONLY);
    int fdOut = open(argv[2], O_WRONLY);
    BUFFSIZE = atoi(argv[3]);

    clock_t start, end;
    float timeUsed;

    if (fdIn == -1 || fdOut == -1)
    {
        perror("Error opening files");
    }

    start = clock();

    ioCopy(fdIn, fdOut); // 0 , 1

    end = clock();

    timeUsed = (float)(end - start) / (float)CLOCKS_PER_SEC;
    printf("Lowlevel copy ended with blocksize %d in %f\n", BUFFSIZE, timeUsed);

    return (0);
}

void ioCopy(int IN, int OUT) // no error reporting
{
    int n;
    char *buffer = malloc(BUFFSIZE);

    while ((n = read(IN, buffer, BUFFSIZE)) > 0)
    {
        if (write(OUT, buffer, n) != n)
        {
            perror("Erro de escrita!\n");
            return;
        }
    }

    if (n < 0)
        perror("Erro de leitura!\n");
}