#include<stdio.h>

int sumFunc(int * pArr, int arrSize) {
  int i, sum = 0;
  
  for (i = 0; i < arrSize; i++)
  {
    sum += pArr[i];
  }

  return sum;
}

int swapFunc(int * num1, int * num2) {
  int aux = *num1;

  *num1 = *num2;
  *num2 = aux;
}

int main() {
  //? Pointers
  int x = 4;
  int * pX = &x; // set's a pointer pointing to an adress of the variable x 
  int y = *pX; // set's a variable with the value of what the pointer is pointing to 

  printf("Value of y = *pX: %d", y);

  //? Pointers with Arrays
  int array[3] = {1, 2, 3};
  int *pArray1, *pArray2;

  // These two syntaxes are the same because the value of "array" is 
  // the address of the first element of the array 
  pArray1 = array;
  pArray2 = &array[0];

  printf("\nValue of the first element of pArray1 = array: %d", pArray1[0]);
  printf("\nValue of the first element of pArray2 = &array[0]: %d", pArray2[0]);

  //? Arithemetic of Pointers
  int num1 = 5; 
  int * pNum1 = &num1;
  
  printf("\nNum1 and pNum1: %d - %d", num1, pNum1); // Example Output: Num1 and pNum1: 5 - 1398799604 
  printf("\nNum1 and pNum1: %d - %d", num1 + 1, pNum1 + 1); // Example Output: Num1 and pNum1: 6 - 1398799608
  // Where we conclude that the sizeof(int) = 4 because (1398799608 - 1398799604) = 4

  int array2[4] = {5, 10, 15, 20};
  int * pArr2 = array2;
  int * pArr2LastElem = &array2[3];

  printf("\nDiference between the pointer of the first element and the last of an array: %d", pArr2LastElem - pArr2);
  //Example: Where we conclude that the (200840 - 200828) / sizeof(int) = 12 / 4 = 3

  //? Access array values with pointers
  int array3[5] = {5, 10, 15, 20, 25};
  int * pArray3 = array3;
  
  // How to access the third element of the array
  int thirdElem1 = array3[2]; 
  int thirdElem2 = *(pArray3 + 2);
  int thirdElem3 = *(array3 + 2);
  int thirdElem4 = pArray3[2];
  
  printf("\nAll the ways to access the third element of an arr: %d %d %d %d", thirdElem1, thirdElem2, thirdElem3, thirdElem4);

  //? Pointers as parameters in functions
  int sum, array4[5] = {1, 2, 3, 4, 5};
  float average;

  sum = sumFunc(array4, 5);
  average = sum / 5;
  printf("\nAverage using pointers and functions: %d", average);

  int numSwap1 = 2, numSwap2 = 1;
  printf("\nnumSwap1 and numSwap2 before the swap: %d %d", numSwap1, numSwap2);
  swapFunc(&numSwap1, &numSwap2);
  printf("\nnumSwap1 and numSwap2 after the swap: %d %d", numSwap1, numSwap2);


}
