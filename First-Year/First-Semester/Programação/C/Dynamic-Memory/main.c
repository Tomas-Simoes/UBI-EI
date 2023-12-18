#include<stdio.h>
#include<stdlib.h>

#include "..\Professor-Libraries\Array1DInteirosMD.h"

int main(){
  int *A, N;

  A = lerArray1DInteirosMD(&N);

  printf("Array with %d size: ", N);
  escreverArray1DInteirosMD(A, N);

  printf("\n\nInverted Array: ");
  inverterArray1DInteiros(A, N);
  escreverArray1DInteirosMD(A, N);
}