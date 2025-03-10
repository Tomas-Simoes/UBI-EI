/* ex72.c : compilar cc -Wall -c ex72.c -o ex72 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#define BUFFSIZE 128
void ioCopy(int IN, int OUT);
int main()
{
    ioCopy(STDIN_FILENO, STDOUT_FILENO); // 0 , 1
    return (0);
}
void ioCopy(int IN, int OUT) // no error reporting
{
    int n;
    char buf[BUFFSIZE];
    while ((n = read(IN, buf, BUFFSIZE)) > 0)
    {
        if (write(OUT, buf, n) != n)
            perror("Erro de escrita!\n");
    }
    if (n < 0)
        perror("Erro de leitura!\n");
}