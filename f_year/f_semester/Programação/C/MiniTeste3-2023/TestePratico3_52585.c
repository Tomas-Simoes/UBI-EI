
/*****************************************************/
// Numero de estudante: 52585
// Nome de estudante: Tomás Simões Duarte
/****************************************************/

#include <stdio.h>

#include "OperacoesBasicas.h"
#include "Array1DReais.h"


int main()
{
  int N = lerNumeroInteiroValido(1, 30);

  float arr[N];
  lerArray1DReais(arr, N);
  
  
  float max = arr[0];
  for (int i = 1; i < N; i++)
  {
    if(arr[i] > 0 && arr[i] > max) {
      max = arr[i];
    }
  }
  
  if(max < 0) {
    printf("There is no positive numbers in the array.");
  } else {
    printf("The max number between the positives of the array is %f.", max);
  }
}
