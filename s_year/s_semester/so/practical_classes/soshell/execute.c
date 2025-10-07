/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

#define MAX_COMMANDS 4

char *safe[MAX_COMMANDS] = {"ls", "cat", "date", "top"};

int safeexec(char *command);

void execute(int *numargs, char **args)
{
  printf("%s", args[0]);
  int pid, status;
  int code = lastArg(numargs, args);

  if ((pid = fork()) < 0)
  {                  /* cria um processo progenito */
    perror("forks"); /* NOTE: perror() produz uma pequema mensagem de erro para o stream */
    exit(1);         /* estandardizado de erros que descreve o ultimo erro encontrado */
                     /* durante uma chamada ao sistema ou funcao duma biblioteca */
  }

  if (pid == 0)
  {
    *numargs = redirects(*numargs, args);
    if (safeexec(args[0]) == 1)
      execvp(*args, args);
    else
    {
      printf("Command invalido\n");
      return; // NOTE: as versoes execv() e
    } // execvp() de execl() sao uteis quando
    perror(*args); /* o numero de argumentos nao e. conhecido.
                    * Os argumentos de  */
    exit(1);       /* execv() e execvp() sao o nome do ficheiro
                    * a ser executado e um */
  } /* vector de strings que contem os
     * argumentos. O ultimo argument */

  if (code == FG)
  {
    while (wait(&status) != pid)
      /*spin fazer nada */;
  }

  return;
}

int safeexec(char *command)
{
  for (int i = 0; i < MAX_COMMANDS; i++)
  {
    if (strcmp(safe[i], command) == 0)
      return 1;
  }

  return 0;
}
int lastArg(int *numargs, char **args)
{
  if (args[*numargs - 1][0] == '&')
  {
    *numargs = *numargs - 1;
    args[*numargs] = NULL;

    return BG;
  }

  return FG;
}
