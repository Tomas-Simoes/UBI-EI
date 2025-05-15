#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int BUFFSIZE;

int ioCopy(int IN, int OUT);

int copy(char *font, char *destination, char *buffsize)
{
    int fdIn = open(font, O_RDONLY);
    int fdOut = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    BUFFSIZE = atoi(buffsize);

    if (fdIn == -1 || fdOut == -1)
    {
        perror("Error opening files");
        if (fdIn != -1)
            close(fdIn);
        if (fdOut != -1)
            close(fdOut);
        return 0;
    }

    int success = ioCopy(fdIn, fdOut);

    close(fdIn);
    close(fdOut);
    return success ? 1 : 0;
}

int ioCopy(int IN, int OUT) // 👈 Return int
{
    int n;
    char *buffer = malloc(BUFFSIZE);
    int ok = 1;

    while ((n = read(IN, buffer, BUFFSIZE)) > 0)
    {
        if (write(OUT, buffer, n) != n)
        {
            perror("Erro de escrita!\n");
            ok = 0;
            break;
        }
    }

    if (n < 0)
    {
        perror("Erro de leitura!\n");
        ok = 0;
    }

    free(buffer);
    return ok;
}
