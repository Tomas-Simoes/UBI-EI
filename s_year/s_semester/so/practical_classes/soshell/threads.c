#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

char strings[MAX][130];
int logIndex = 0;

void warning(char *msg, int time)
{
    while (time > 0)
    {
        sleep(1);
        time--;
    }

    fprintf(stderr, "Aviso: %s\n", msg);
}

void *avisoWrapper(void *args)
{
    aviso_t *ptr = (aviso_t *)args;
    warning(ptr->msg, ptr->tempo);

    free(ptr);
    return NULL;
}

void *copyWrapper(void *args)
{
    copy_t *ptr = (copy_t *)args;

    time_t tempoAtual;
    time(&tempoAtual);

    char *diaHora = ctime(&tempoAtual);

    if (diaHora[strlen(diaHora) - 1] == '\n')
        diaHora[strlen(diaHora) - 1] = '\0';

    int success = copy(ptr->font, ptr->destination, ptr->buffsize); // Return 1 on success, 0 on error

    char resultEntry[130];
    snprintf(resultEntry, sizeof(resultEntry), "%s %s (%s)", diaHora, ptr->font, success ? "success" : "fail");

    if (logIndex < MAX)
    {
        strncpy(strings[logIndex], resultEntry, 129);
        strings[logIndex][129] = '\0';
        logIndex++;
    }

    free(ptr);

    return NULL;
}

void printCopyLogs()
{
    for (int i = 0; i < MAX; i++)
    {
        if (strlen(strings[i]) > 0)
        { // Only print non-empty strings
            printf("%s\n", strings[i]);
        }
    }
}
