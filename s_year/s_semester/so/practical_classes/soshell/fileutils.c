#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void biggestFile(char *file1, char *file2)
{
    struct stat infoFile1;
    struct stat infoFile2;

    if (stat(file1, &infoFile1) == -1 || stat(file2, &infoFile2) == -1)
    {
        perror("Erro ao acessar informações sobre o ficheiro");
        return;
    }

    if (infoFile1.st_size > infoFile2.st_size)
        printf("O ficheiro '%s' é o maior com tamanho %ldKB\n", file1, infoFile1.st_size / 1024);
    else if (infoFile2.st_size > infoFile1.st_size)
        printf("O ficheiro '%s' é o maior com tamanho %ldKB\n", file2, infoFile2.st_size / 1024);
    else
        printf("Os ficheiros têm o mesmo tamanho: %ldKB\n", infoFile1.st_size / 1024);
}

void execPermission(char *file)
{
    struct stat infoFile;

    if (stat(file, &infoFile) == -1)
    {
        perror("Erro ao acessar informações sobre o ficheiro");
        return;
    }

    mode_t newMode = infoFile.st_mode | S_IXUSR;

    if (chmod(file, newMode) == -1)
    {
        perror("Erro ao mudar as permissões do ficheiro");
        return;
    }

    printf("Permissão de execucação foi atribuida ao ficheiro %s", file);
}

void removeReadPermission(char *file)
{
    struct stat infoFile;

    if (stat(file, &infoFile) == -1)
    {
        perror("Erro ao acessar informações sobre o ficheiro");
        return;
    }

    /*
        S_IRGRP | S_IROTH = 0040 | 0004 = 0044 = read_permission
        ~read_permission = inverted_permissions
        st_mode & inverted_permissions -> will remove those permissions from st_mode
    */
    mode_t newMode = infoFile.st_mode & ~(S_IRGRP | S_IROTH);

    if (chmod(file, newMode) == -1)
    {
        perror("Erro ao mudar as permissões do ficheiro");
        return;
    }

    printf("Permissões de leitura para grupo e outros removidas do ficheiro '%s'.\n", file);
}

void dirInfo(char *dirName)
{
    if (dirName == NULL)
        dirName = ".";

    DIR *dir = opendir(dirName);

    if (dir == NULL)
    {
        perror("Erro ao abrir o diretório");
        return;
    }

    struct dirent *entry;
    struct stat infoFile;
    char completeDir[1024];
    char timeBuffer[100];

    while ((entry = readdir(dir)) != NULL)
    {
        snprintf(completeDir, sizeof(completeDir), "%s/%s", dirName, entry->d_name);

        if (stat(completeDir, &infoFile) == -1)
        {
            perror("Erro ao acessar informações sobre o ficheiro");
            continue;
        }

        struct tm *timeInfo = localtime(&infoFile.st_mtime);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);

        printf("Nome: %-20s (%ld KB) | Inode: %-10ld | Last Modification: %s\n", entry->d_name, infoFile.st_size / 1024, (long)entry->d_ino, timeBuffer);
    }

    closedir(dir);
}