#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <io.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define PAUSA(A)             \
  {                          \
    fflush(stdin);           \
    printf("Pausa %s\n", A); \
    getchar();               \
  }

// velocidade das pausas do programa programa
float acel = 1.0;
#define pausa                               \
  {                                         \
    float indicez1;                         \
    for (indicez1 = 0; indicez1 < 200000;   \
         indicez1 = indicez1 + 0.01 * acel) \
      ;                                     \
  }

#define RESET 0
#define BRIGHT 1
#define DIM 2
#define UNDERLINE 3
#define BLINK 4
#define REVERSE 7
#define HIDDEN 8
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

void textcolor(int attr, int fg, int bg)
{
  char command[32];
  /* Command is the control command to the terminal */
  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  printf("%s", command);
}

/*
textcolor(BRIGHT, RED+id, BLACK);
  printf	....
textcolor(RESET, BLACK, WHITE);

*/
