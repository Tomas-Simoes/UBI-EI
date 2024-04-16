#include <stdio.h>

int getNaoDivisores(int A, int M)
{
  int i, naoDivisores = 0;

  for (i = 1; i <= M; i++)
  {
    if (A % i != 0)
      naoDivisores++;
  }

  return naoDivisores;
}

int main()
{
  int num1 = 0, num2 = 0, naoDivisores = 0;

  do
  {
    printf("Insira um numero entre 100 e 400: ");
    scanf("%d", &num1);
  } while (num1 < 100 || num1 > 400);

  do
  {
    printf("\n Insira outro numero entre 50 e 80: ");
    scanf("%d", &num2);
  } while (num2 < 50 || num2 > 80);

  naoDivisores = getNaoDivisores(num1, num2);

  printf("\n\nA quantidade de numeros nao divisores de %d entre 1 e %d e: %d", num1, num2, naoDivisores);
}