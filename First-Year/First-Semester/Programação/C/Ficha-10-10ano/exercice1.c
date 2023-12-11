#include<stdio.h>

int main() {
  int soma = 0, produto = 1, num1;

  printf("Insert a number: ");
  scanf("%d", &num1);

  for (int i = 1; i <= num1; i++)
  {
    soma += i;
    produto *= i;
  }

  printf("%d %d", soma, produto);
}