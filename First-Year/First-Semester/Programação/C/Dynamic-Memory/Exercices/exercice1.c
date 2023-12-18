#include<stdio.h>
#include<stdlib.h>

int main() {
  int arraySize;

  printf("Insert a number: ");
  scanf("%d", &arraySize);

  int * array = (int *) malloc (arraySize * sizeof(int));

  for (int i = 0; i < arraySize; i++)
  {
    printf("Insert numbers for the array: ");
    scanf("%d", &array[i]);
  }
  
  array = (int *) realloc(array, (arraySize + 100) * sizeof(int));
  free(array);
}