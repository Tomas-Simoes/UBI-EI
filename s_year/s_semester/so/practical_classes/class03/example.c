/* ex71.c : compilar cc -Wall -c ex71.c -o ex71 */
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd, i, vec[10];

    for (i = 0; i < 10; i++)
        vec[i] = i + 512;
    fd = creat("test.bin", S_IRUSR | S_IWUSR);

    write(fd, vec, sizeof(int) * 10);

    return (0);
}