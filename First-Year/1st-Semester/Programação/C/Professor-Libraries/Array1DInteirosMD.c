int *lerArray1DInteirosMD(int *tam) {
  int *arr, num;

  *tam = 0;
  arr = (int *) malloc(sizeof(int));

  if (arr == NULL) return NULL;

  do
  {
    printf("Insira um numero (< 0 para terminar): ");
    scanf("%d", &num);

    if (num >= 0) {
      *tam = *tam + 1;
      arr = (int *) realloc(arr, *tam * sizeof(int));
      arr[*tam - 1] = num;
    }
  } while (num >= 0);

  return arr;
}

void escreverArray1DInteirosMD (int *A, int N)
{
  int k;
  
  for (k = 0; k < N; k++){
  	printf("%d ", A[k]);
  }
  printf("\n");
}

void inverterArray1DInteiros (int *X, int N) {
  int i, j, aux; 

  i = 0;
  j = N-1;

  while (i < j)
  {
    aux = X[i];
    
    X[i] = X[j]; 
    X[j] = aux;

    i += 1;
    j -= 1;
  }
}