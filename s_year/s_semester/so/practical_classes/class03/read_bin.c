/* ex71.c : compilar cc -Wall -c ex71.c -o ex71 */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int file, rd;

    file = open("./test.bin", O_RDONLY);

    if (file == -1)
    {
        printf("Error opening file.\n");
        return -1;
    }

    int file_size = 10;

    void *buffer = malloc(file_size * sizeof(int));
    int res = read(file, buffer, file_size * 4);
    printf("res %d\n", res);

    if (res == -1)
    {
        perror("read");
    }
    else
    {
        for (int i = 0; i < file_size; i++)
        {
            printf("%d  ", *(int *)(buffer + (i * 4)));
        }
    }

    return (0);
}