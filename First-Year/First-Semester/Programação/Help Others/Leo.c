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

/*

n = 3

2 - maior é o 2
---
10 maior dos 3 é 10
---
15
---

loop enquanto o numero de numeros que nos metemos for menor que N 
*/
