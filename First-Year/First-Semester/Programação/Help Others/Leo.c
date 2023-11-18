#include<stdio.h>

int main() {

int num;
int soma=0;
  printf("Introduza numeros inteiros:");
  scanf("%d", &num);
  soma = 0 + num;
  while(num>0){
    scanf("%d", &num);
    soma = soma + num; //soma += num 
  }
  printf("%d", soma);
}

