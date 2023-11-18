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
