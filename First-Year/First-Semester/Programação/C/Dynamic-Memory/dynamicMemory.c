#include<stdio.h>
#include<stdlib.h>

int main() {
  //? Allocate memory with calloc
  float *pCalloc, *pMalloc;

  // Allocates memory for a chunck of 200 float numbers
  // basically an 1D array of floats.
  pCalloc =  (float *) calloc(200, sizeof(float)); 

  //? Allocate memory with malloc
  // Exactly the same thing as above
  pMalloc = (float *) malloc(200 * sizeof(float));

  //? Reallocate memory
  pMalloc = (float *) realloc(pMalloc, 100 * sizeof(float));

  //? Free memory
  free(pMalloc);
}