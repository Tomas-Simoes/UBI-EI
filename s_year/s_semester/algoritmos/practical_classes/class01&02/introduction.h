typedef struct {
  int numAluno;
  float notasMPT[2];
  float notasTE[2];
  int notaFinal;
} ALUNO;

ALUNO* readArr(int* N) { 
  ALUNO* arr;
  int k, i, num, existsNum;
  
  *N = randomInt(1, 30);
  arr = (ALUNO*) malloc(*N * sizeof(ALUNO));
  
  k = 0;
  existsNum = 0;
  while (k < *N)
  {
    num = randomInt(70000, 75000);
    i = 0;

    while (i < k && existsNum == 0)
    {
      if (arr[i].numAluno == num) {
        existsNum = 1;
      }
      
      i++;
    };

    if (existsNum == 0) {
      arr[k].numAluno = num;
      
      arr[k].notasTE[0] = randomFloat(0.0, 8.0);
      arr[k].notasTE[1] = randomFloat(0.0, 8.0);
      
      arr[k].notasMPT[0] = randomFloat(0.0, 2.0); 
      arr[k].notasMPT[1] = randomFloat(0.0, 2.0); 
    }   

    k++;
  };

  return arr;    
}

void writeArr(ALUNO* arr, int N) {
  for (int i = 0; i < N; i++)
  {
    printf("%d: ", arr[i].numAluno);
    printf("%.2f - %.2f - ", arr[i].notasMPT[0], arr[i].notasMPT[1]);
    printf("%.2f - %.2f - ", arr[i].notasTE[0], arr[i].notasTE[1]);
    printf("%d", arr[i].notaFinal);
    printf("\n");
  }
}

void updateArr(ALUNO* arr, int N) {
  float soma;

  for (int i = 0; i < N; i++)
  {
    soma = arr[i].notasMPT[0] + arr[i].notasMPT[1] + arr[i].notasTE[0] + arr[i].notasTE[1];
    arr[i].notaFinal = soma;
  }
}

int higherFinalGrade_REC(ALUNO* arr, int N) {
  int higher;

  if (N == 1) {
    return arr[0].notaFinal;
  }

  higher = higherFinalGrade_REC(arr, N-1);
  
  if (higher > arr[N-1].notaFinal) {
    return higher;
  } else {
    return arr[N-1].notaFinal;
  }
}