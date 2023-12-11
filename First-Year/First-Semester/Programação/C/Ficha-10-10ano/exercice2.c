#include <stdio.h>

int main()
{
  int pairNumbers = 0;

  for (int i = 1; i <= 10; i++)
  {
    if (i % 2 == 0)
    {
      pairNumbers++;
      printf("Numero par %d: %d\n", pairNumbers, i);
    }
  }
}