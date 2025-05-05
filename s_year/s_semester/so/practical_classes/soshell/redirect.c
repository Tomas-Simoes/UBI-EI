#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FILE_MODE 0644

int dupandclose(int fd, int fdold, int numargs, char *args[])
{
    if (fd < 0 || fdold < 0)
    {
        perror("Invalid fds");
        exit(1);
    }

    dup2(fd, fdold);
    close(fd);

    args[numargs - 1] = NULL;
    return numargs - 1;
}

int redirects(int numargs, char *args[])
{
    if (numargs < 3)
    {
        return numargs;
    }

    if (strcmp(args[numargs - 1], "2>") == 0)
    {
        int fd = creat(args[numargs], FILE_MODE);
        numargs = dupandclose(fd, STDERR_FILENO, numargs, args);
    }

    if (strcmp(args[numargs - 1], ">>") == 0)
    {
        int fd = open(args[numargs], O_CREAT | O_APPEND | O_WRONLY, FILE_MODE);
        numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
    }

    if (strcmp(args[numargs - 1], ">") == 0)
    {
        int fd = creat(args[numargs], FILE_MODE);
        numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);
    }

    if (strcmp(args[numargs - 1], "<") == 0)
    {
        int fd = open(args[numargs], O_RDONLY);
        numargs = dupandclose(fd, STDIN_FILENO, numargs, args);
    }

    return numargs;
}

int redirects_test(int numargs, char *args[])
{
    int i = 0;

    if (numargs < 3)
    {
        return numargs;
    }

    while (i < numargs)
    {
        if (strcmp(args[i], "2>") == 0)
        {
            int fd = creat(args[i + 1], FILE_MODE);
            numargs = dupandclose(fd, STDERR_FILENO, numargs, args);

            i += 2;
        }
        else if (strcmp(args[i], ">") == 0)
        {
            int fd = creat(args[i + 1], FILE_MODE);
            numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);

            i += 2;
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            int fd = open(args[i + 1], O_CREAT | O_APPEND | O_WRONLY, FILE_MODE);
            numargs = dupandclose(fd, STDOUT_FILENO, numargs, args);

            i += 2;
        }
        else if (strcmp(args[i], "<") == 0)
        {
            int fd = open(args[i + 1], O_RDONLY);
            numargs = dupandclose(fd, STDIN_FILENO, numargs, args);

            i += 2;
        }
        else
        {
            i++;
        }
    }

    return numargs;
}