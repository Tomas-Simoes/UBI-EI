#include<stdio.h>
#include<stdlib.h>

int exercice2Func(int N, int * positiveSum, int * positiveQuantity) {
  int num1;
  
  for (int i = 0; i < N; i++)
  {
    printf("Insert a number: ");
    scanf("%d", &num1);

    if(num1 > 0) {
      *positiveSum += num1;
      *positiveQuantity += 1;
    }
  }
}

int exercice3Func(int arr[], int arrSize) {
  int i;
  int smallestNum = -1;

  for (i = 0; i < arrSize; i++)
  {
    if(arr[i] > 0 && (arr[i] < smallestNum || smallestNum < 0)) {
      smallestNum = arr[i];
    }
  }
  
  return smallestNum;
}

typedef struct 
{
  int numAluno;
  int notaFinal;
  int aprovado;
} ALUNO;

//? Functions in Frequencia2.h
//void lerArray1DALUNO (ALUNO A[], int *N);
//void mostrarArray1DALUNO (ALUNO A[], int N);
/*
int exercice4Func(){
  int TAM;
  do
  {
  
    printf("Insert the size: ");
    scanf("%d", &TAM);
  } while (TAM < 0 || TAM > 100);
  
  ALUNO arrAlunos[TAM];

  lerArray1DALUNO(arrAlunos, &TAM);
  
  for (int i = 0; i < TAM; i++)
  {
    if (arrAlunos[i].notaFinal > 10)
    {
      arrAlunos[i].aprovado = 1;
    } else {
      arrAlunos[i].aprovado = 0;
    }
  }

  mostrarArray1DALUNO(arrAlunos, TAM);  
}
*/
int main() {
  //? Exercice 1
  /*
    a) 100700 
    b) 600
    c) 110160 + 4 * sizeof(int) = 110176
    d) 700
    e) *110160 + 4 = 50 + 4 = 54
    f) *(110160 + 2 * sizeof(int)) = *110168 = 150
    g) 110168 + 4 * sizeof(int) = 110168 + 16 = 110184
    h) 100700 + 4 * sizeof(int *) = 100700 + 36 = 100736
  */

  //? Exercice 2
  /*
  printf("-- Exercice 2 --\n\n");

  int N, positiveSumEx2 = 0, positiveQuantityEx2 = 0;
  
  printf("Insert N: ");
  scanf("%d", &N);
  
  exercice2Func(N, &positiveSumEx2, &positiveQuantityEx2);
  printf("The sum of the %d positive numbers is %d.", positiveQuantityEx2, positiveSumEx2);
  */

  //? Exercice 3
  /*
  printf("-- Exercice 3 --\n\n");

  int arr[4] = {7, -5, -2, 4};
  int smallestPositiveNumber = exercice3Func(arr, 4);

  printf("The smallest positive number is: %d", smallestPositiveNumber);
  */
  //? Exercice 4
  /*
  printf("-- Exercice 4 --\n\n");
  exercice4Func()
  */
  //? Exercice 5
  FILE * entrada = fopen("entrada.txt", "r");
  FILE * saida = fopen("saida.txt", "w");

  int num1, num2;
  while ((fscanf(entrada, "%d %f", &num1, &num2)) == 2)
  {
    if(num1 > 0) {
      fprintf(saida, "%d %f\n", num1, num2);
    }
  }

  fclose(entrada);
  fclose(saida);
}

