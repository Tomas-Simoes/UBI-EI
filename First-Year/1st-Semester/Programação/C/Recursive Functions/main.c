#include<stdio.h>

int getPow(int n){
  if(n == 0){
    return 1;
  } else {
    return 2 * getPow(n-1);
  }
}

int getStringLen(char str[], int currentChar) {
  if(str[currentChar] == '\0'){
    return 0;
  } else {
    return 1 + getStringLen(str, currentChar + 1);
  }
}

int getFibonnaci(int previous, int num, int n){
  if(n > 0){
    return getFibonnaci(num, num + previous, n - 1); 
  }
}

// not completed
int getEuclides(int num1, int num2){
  if(num2 > 0){
    return getEuclides(num2, num1 / num2);
  } else { 
    return num1;
  }
}

#define ARR_SIZE 5
int getHigher(int arr[], int i) {
  int higher;

  if(i == 1)
    return arr[0];
  
  higher = getHigher(arr, i-1);

  if(higher >= arr[i-1]) 
    return higher;
  
  return arr[i-1];
}

// not completed
int getHigherODD(int arr[], int i) {
  int higherOdd;

  if(i == 1) {
    if(arr[0] % 2 == 0) 
      return arr[0];
    else 
      return -1;
  }

  higherOdd = getHigherODD(arr, i-1);

  if(higherOdd == -1) {
    if(arr[i-1] % 2 == 0) 
      return arr[i-1];
    
    return -1; 
  } else {
    if(arr[0] % 2 == 0)
      if (higherOdd > arr[0])
        return higherOdd;
      
      return arr[0];
  }
}

int main(){
  printf("\nExercice 1: %d", getPow(6));
  printf("\nExercice 2: %d", getStringLen("Mekie caralho", 0));
  printf("\nExercice 4:  %d", getFibonnaci(0, 1, 9));
  //printf("\nExercice 6:  %d", getEuclides());

  int myArr[] = {3, 6, 2, 7, 3}; 
  printf("\nExercice 7: %d", getHigher(myArr, ARR_SIZE));
  printf("\nExercice 14: %d", getHigherODD(myArr, ARR_SIZE));
}