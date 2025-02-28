#include <stdio.h>
#include <stdlib.h>

#include "../../lib/Aleatorio.h"
#include "introduction.h"

int main() {
  int tamArr;
  ALUNO* arr = readArr(&tamArr);
  
  printf("Size of arr: %d\n", tamArr);
  writeArr(arr, tamArr);

  updateArr(arr, tamArr);
  printf("\nUpdated arr: \n");
  writeArr(arr, tamArr);

  int higherGrade = higherFinalGrade_REC(arr, tamArr);
  printf("\nHighest grade: %d", higherGrade);
}
