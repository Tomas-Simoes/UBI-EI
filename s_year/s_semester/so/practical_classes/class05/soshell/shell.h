#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/wait.h>

int parse(char *buf, char **args);

void execute(int *numargs, char **args);

int builtin(int *numargs, char **args);

int lastArg(int *numargs, char **args);

void copy(char *font, char *destination, char *buffsize);

// socalc.c

void calc(char *value1, char *op, char *value2);
void bits(char *value1, char *op, char *value2);

// sotypes.c
int isJPG(char *filePath);

// redirect.c
int dupandclose(int fd, int fdold, int numargs, char *args[]);
int redirects(int numargs, char *args[]);

/* constantes que podem tornar uteis*/
#define BG 0
#define FG 1
