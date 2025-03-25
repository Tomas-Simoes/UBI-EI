#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *args[2] = {"date", NULL};

    int status, pid, x = 9;

    pid = fork();
    if (0 == pid)
    {
        x++;
        pid = fork();

        if (0 == pid)
            execvp(*args, args);
        else
            wait(&status);
    }
    else
        x--;

    printf("x=%d\n", x);
}