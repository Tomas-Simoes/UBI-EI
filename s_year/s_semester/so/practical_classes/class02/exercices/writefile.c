#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) // permissões típicos

char buf1[] = "Sistemas Operativos 2024\n";

int main()
{
    int fd;

    if (access("test.txt", F_OK) != -1)
    {
        if ((fd = open("test.txt", O_APPEND | O_WRONLY | O_CREAT, FILE_MODE)) < 0)
        {
            perror("Erro na abertura do ficheiro. \n");
            return 1;
        }
    }
    else
    {
        if ((fd = creat("test.txt", O_APPEND | O_WRONLY | FILE_MODE)) < 0)
        {
            perror("Erro na criacao de ficheiro!\n");
            return 1;
        }
    }

    if (write(fd, buf1, sizeof(buf1) - 1) != sizeof(buf1) - 1)
        perror("Erro de escrita em buf1!\n");

    return (0);
}