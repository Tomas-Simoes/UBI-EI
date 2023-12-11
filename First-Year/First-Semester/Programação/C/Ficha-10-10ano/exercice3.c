#include <stdio.h>

int main()
{
  int num1;
  printf("Insert a number: ");
  scanf("%d", &num1);

  for (int i = 1, z = num1; i <= num1 && z >= 1; i++, z--)
  {
    printf("\n%d %d", i, z);
  }
}