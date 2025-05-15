#include "shell.h"
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>
typedef struct
{
  char arr[10][PATH_MAX];
  int top;
} Stack;

void initializeStack(Stack *stack)
{
  stack->top = -1;
}

void push(Stack *stack, char *value)
{
  if (stack->top < 9)
  {
    stack->top++;
    strcpy(stack->arr[stack->top], value);
  }
  else
  {
    perror("stack overflow\n");
  };
}

char *pop(Stack *stack)
{
  if (stack->top == -1)
  {
    perror("stack underflow\n");
    return NULL;
  }

  char *popped = stack->arr[stack->top];
  stack->top--;

  return popped;
}

char prompt[100];
Stack dirStack;

int main()
{
  int len;
  char command[1024]; /* um comando */
  char *args[64];     /* com um maximo de 64 argumentos */
  initializeStack(&dirStack);

  strcpy(prompt, "SOSHELL: Introduza um comando : prompt>");

  while (1)
  {
    printf("%s", prompt);

    // command is null
    if (fgets(command, 1023, stdin) == NULL)
    {
      printf("\n");
      exit(0);
    }

    len = strlen(command);

    if (1 == len)
      continue; /* linha é apenas \n */

    // formats command with string terminator
    if (command[len - 1] == '\n')
      command[len - 1] = '\0';

    int numargs = parse(command, args); /* particiona a string em argumentos */

    if (!builtin(&numargs, args))
      execute(&numargs, args); /* executa o comando */
  }

  return 0;
}

int builtin(int *numargs, char **args)
{

  if (strcmp(args[0], "sair") == 0)
  {
    exit(0);
    return 1; /* funcionalidade embutida */
  }

  if (strncmp(args[0], "42", 2) == 0)
  {
    printf("42 is the answer to life the universe and everything\n");
    printf("https://pt.wikipedia.org/wiki/The_Hitchhiker's_Guide_to_the_Galaxy\n");
    return 1; /* funcionalidade embutida */
  }

  if (strcmp(args[0], "getinfo") == 0)
  {
    printf("SO Shell 2025 version 1.0\n");
    return 1;
  }

  if (strlen(args[0]) > 4 && strncmp(args[0], "PS1=", 4) == 0)
  {
    strcpy(prompt, args[0] + 4);
    return 1;
  }

  if (strcmp(args[0], "whoami") == 0)
  {
    system("id");
    return 1;
  }

  if (strcmp(args[0], "cd") == 0)
  {
    int isPrevDir = 0;
    int res;

    char curDir[PATH_MAX];
    char *nextDir;

    if (args[1] == NULL || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)
    {
      nextDir = getenv("HOME");
    }
    else if (strcmp(args[1], "-") == 0)
    {
      nextDir = pop(&dirStack);
      isPrevDir = 1;
    }
    else
    {
      nextDir = args[1];
    }

    if (isPrevDir == 0)
    {
      getcwd(curDir, sizeof(curDir));
      printf("%s\n", curDir);
      push(&dirStack, curDir);
    }

    res = chdir(nextDir);
    if (res < 0)
      perror(args[1]);

    return 1;
  }

  if (strcmp(args[0], "socp") == 0)
  {
    if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
    {
      copy(args[1], args[2], args[3]);
    }
    else
    {
      printf("Invalid Syntax:\nUsage: socp font destination");
    }

    return 1;
  }

  if ((strcmp(args[0], "calc") == 0) && (*numargs == 3))
  {
    calc(args[1], args[2], args[3]);
    return 1;
  }

  if (strcmp(args[0], "bits") == 0)
  {
    bits(args[1], args[2], args[3]);
    return 1;
  }

  if (strcmp(args[0], "isjpg") == 0)
  {
    printf("File %s JPG", isJPG(args[1]) ? "is" : "is not");
    return 1;
  }

  if (strcmp(args[0], "aviso") == 0)
  {
    pthread_t th;
    aviso_t *ptr = (aviso_t *)malloc(sizeof(aviso_t));

    strcpy(ptr->msg, args[1]);
    ptr->tempo = atoi(args[2]);

    pthread_create(&th, NULL, avisoWrapper, (void *)ptr);

    return 1;
  }

  if (strcmp(args[0], "socpthread") == 0)
  {
    pthread_t th;
    copy_t *ptr = (copy_t *)malloc(sizeof(copy_t));

    ptr->font = strdup(args[1]);
    ptr->destination = strdup(args[2]);
    ptr->buffsize = strdup(args[3]);

    pthread_create(&th, NULL, copyWrapper, (void *)ptr);

    return 1;
  }

  if (strcmp(args[0], "InfoCopias") == 0)
  {
    printCopyLogs();
    return 1;
  }

  return 0;
}
