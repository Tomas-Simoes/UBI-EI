#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int BUFFSIZE;

void ioCopy(int IN, int OUT);

void copy(char *font, char *destination, char *buffsize)
{
    int fdIn = open(font, O_RDONLY);
    int fdOut = open(destination, O_WRONLY);
    BUFFSIZE = atoi(buffsize);

    if (fdIn == -1 || fdOut == -1)
    {
        perror("Error opening files");
    }

    ioCopy(fdIn, fdOut);

    printf("Lowlevel copy ended.\n");
}

void ioCopy(int IN, int OUT)
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
};