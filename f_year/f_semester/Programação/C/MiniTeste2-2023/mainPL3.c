#include <stdio.h>

int productBetweenTwoNumbers(int A, int B)
{
  int totalProduct = 1;

  for (int i = A; i <= B; i++)
  {
    if (i % 2 == 1)
      totalProduct *= i;
  }

  return totalProduct;
}

int main()
{
  int num1, num2, product;

  do
  {
    printf("Insert two integers between 20 and 50: ");
    scanf("%d %d", &num1, &num2);

  } while (num1 < 20 || num2 < 20 || num1 > 50 || num2 > 50);

  if (num1 > num2)
    product = productBetweenTwoNumbers(num2, num1);
  else
    product = productBetweenTwoNumbers(num1, num2);

  printf("\nThe final product is: %lld", product);
}