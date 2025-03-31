#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int isJPG(char *filePath)
{
    int fileDescriptor = open(filePath, O_RDONLY);
    unsigned char b[4];

    if (fileDescriptor == -1)
    {
        perror("Error opening file");
        return -1;
    }

    int n = read(fileDescriptor, b, 4);

    if (n)
    {
        lseek(fileDescriptor, 0, SEEK_SET);
    }

    if (0xff == b[0] && 0xd8 == b[1] && 0xff == b[2] && 0xe0 == b[3])
    {
        return 1;
    }

    return 0;
}