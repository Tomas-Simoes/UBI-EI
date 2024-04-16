#include<stdio.h>

int produto(int A, int B) {
  int produtoTotal = 1;

  for (int i = A; i <= B; i++)
  {
    produtoTotal = produtoTotal * i;
  }
  return produtoTotal; 
}

int main(){
  int num1, num2, numeroMaior, numeroMenor = 0;

  do
  {
    printf("\nInsere dois numeros inteiros entre 20 e 50: ");
    scanf("%d %d", &num1, &num2);

    if(num1 > num2) {
      numeroMaior = num1;
      numeroMenor = num2;
    } else {
      numeroMaior = num2;
      numeroMenor = num1;
    }
  } while (numeroMaior > 50 || numeroMenor < 20);
  
  printf("O produto de todos os numeros entre %d e %d: %d", numeroMenor, numeroMaior, produto(numeroMenor, numeroMaior));
}