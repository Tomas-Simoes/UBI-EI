
// ler um array 1D de reais de tamanho N
void lerArray1DReais (float A[], int N)
{
  int k;
  
  for (k = 0; k < N; k++){
  	printf("Insira um numero real: ");
  	scanf("%f", &A[k]);
  }
  
}

// escrever no monitor um array 1D de reais de tamanho N
void escreverArray1DReais (float A[], int N)
{
  int k;
  
  for (k = 0; k < N; k++){
  	printf("%.3f ", A[k]);
  }
  printf("\n");
}

