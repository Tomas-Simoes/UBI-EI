#include "bancos.h"
#include <unistd.h>
#include <semaphore.h>

// escolhe um nome para o tipo de dados
typedef struct
{
  int idAtm;
  int idCliente;
  float valor;
} transaction;

// Max numero de clientes e threads
#define MAXCLI 20
#define MAXT 10

/* variaveis partilhadas pelos threads */
int NT;
int NC;
int cnt;

pthread_mutex_t clientLocks[MAXCLI];
pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

sem_t isThreadFinished;

float saldos[MAXCLI];

void *relatorio(void *args);
void *multibanco(void *args);

int main(int argc, char *argv[])
{
  int i;
  int threadIds[MAXT];
  pthread_t rel, atm[MAXT];
  sem_init(&isThreadFinished, 0, 0);
  printf("\n\nIntroduza o numero de ATM's (ate 10) e numero de clientes (ate 20):  ");
  scanf("%d%d", &NT, &NC);

  printf("Data in.bin. Voce Escolheu:  Threads= %d Clientes=%d\n\n", NT, NC);
  getchar(); // engolir /n

  pthread_mutex_t clientLocks[NC];
  for (i = 0; i < NC; i++)
    pthread_mutex_init(&clientLocks[i], NULL);

  for (i = 0; i < NC; i++)
    saldos[i] = 0.0;

  cnt = -NT;

  pthread_create(&rel, NULL, relatorio, NULL);

  for (i = 0; i < NT; i++)
  {
    threadIds[i] = i;
    pthread_create(&atm[i], NULL, multibanco, (void *)&threadIds[i]);
  }

  for (i = 0; i < NC; i++)
    pthread_mutex_destroy(&clientLocks[i]);

  pthread_mutex_destroy(&count_lock);

  pthread_exit(NULL);
}

void *multibanco(void *args)
{
  int threadId = *(int *)args;

  int fd = open("in.bin", O_RDONLY);

  if (fd < 0)
    perror("Erro na thread");

  transaction *buffer = malloc(sizeof(transaction));

  while (read(fd, buffer, sizeof(transaction)) > 0)
  {
    if (buffer->idAtm == threadId)
    {

      pthread_mutex_lock(&clientLocks[buffer->idCliente]);
      float clientBalance = saldos[buffer->idCliente];
      pausa;

      saldos[buffer->idCliente] = clientBalance + buffer->valor;
      pthread_mutex_unlock(&clientLocks[buffer->idCliente]);

      textcolor(BRIGHT, RED + (threadId % 7), BLACK);
      printf("New transaction at ATM %d on client %d with value %f.\n",
             buffer->idAtm, buffer->idCliente, buffer->valor);
      textcolor(RESET, BLACK, BLACK);
    }
  }

  pthread_mutex_lock(&count_lock);
  cnt++;
  pthread_mutex_unlock(&count_lock);

  if (cnt == 0)
    sem_post(&isThreadFinished);

  free(buffer);
  close(fd);

  return NULL;
}

void *relatorio(void *args)
{
  sem_wait(&isThreadFinished);

  textcolor(UNDERLINE, WHITE, BLACK);
  printf("Relatório do Fim do Dia:\n");

  textcolor(RESET, WHITE, BLACK);
  printf("%-10s %10s\n", "Cliente", "Saldo");

  for (int i = 0; i < NC; i++)
  {
    printf("%-10d %10.2f\n", i, saldos[i]);
  }

  return NULL;
}
