
/*****************************************************/
// Numero de estudante: Tomás Simões Duarte
// Nome de estudante: 52585
/****************************************************/

#include <stdio.h>

// ler e devolver um inteiro entre inf e sup
int lerNumeroInteiroValido (int inf, int sup)
{
  int aux, num;
  if (inf > sup)
  { 
  	aux = inf;
  	inf = sup;
  	sup = aux;
  }
  do{
  	printf("Insira um inteiro entre %d e %d: ", inf, sup);
  	scanf("%d", &num);
  }while(num < inf || num > sup);
  return num;
}

// ler um array 1D de inteiros de tamanho N
void lerArray1DInteiros (int A[], int N)
{
  int k;
  for (k = 0; k < N; k++)
  {
  	printf("Insira um numero inteiro: ");
  	scanf("%d", &A[k]);
  }
}

int sum(int arr[], int minHigher, int i){
  if(i == 1) {
    if (arr[0] > minHigher) 
      return arr[0];
    
    return 0;
  }

  if (arr[i-1] > minHigher)
    return arr[i-1] + sum(arr, minHigher, i-1);

  return 0;
}

// implementar funcao/subprograma recursivo aqui
int main()
{
  int num = lerNumeroInteiroValido(0, 20);
  
  int arr[num];
  lerArray1DInteiros(arr, num);

  int minHigher = lerNumeroInteiroValido(0, 100);
  int totalSum = sum(arr, minHigher, num);

  if(totalSum == 0) {
    printf("There is no number higher than %d", minHigher);
  } else {
    printf("The sum is: %d", totalSum);
  }
}
