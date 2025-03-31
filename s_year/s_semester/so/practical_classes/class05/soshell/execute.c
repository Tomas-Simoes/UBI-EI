/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

void execute(int *numargs, char **args)
{
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
    execvp(*args, args); /* NOTE: as versoes execv() e
                          * execvp() de execl() sao uteis quando */
    perror(*args);       /* o numero de argumentos nao e. conhecido.
                          * Os argumentos de  */
    exit(1);             /* execv() e execvp() sao o nome do ficheiro
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
