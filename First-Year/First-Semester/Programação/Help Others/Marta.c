#include<stdio.h>
int main(int argc, char const *argv[])
{
  int num = 0;
  int soma = 0;

  printf("Introduza um nº");
  scanf("%d", &num);

  while (num >= 0)
  {
    soma += num;  
    
    printf("Introduza um nº");
    scanf("%d", &num);
  }
  
  printf("Soma: " + soma);
    
  return 0;
}

/* 

n = 3

1 - maior é 1
2 - 2 > 1 entao o maior é o 2
3 - 3 > 2 entao o maior é o 3

*/
