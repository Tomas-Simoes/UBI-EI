void lerArray1DInteiros(int A[], int N)
{
  int k;

  for (k = 0; k < N; k++)
  {
    printf("Insira um numero inteiro: ");
    scanf("%d", &A[k]);
  }
}

void escreverArray1DInteiros(int A[], int N)
{
  int k;

  for (k = 0; k < N; k++)
  {
    printf("%d ", A[k]);
  }
  printf("\n");
}

int somaArray1DInteiros(int A[], int N)
{
  int i, soma = 0;

  for (i = 0; i < N; i++)
  {
    soma += A[i];
  }

  return soma;
}
