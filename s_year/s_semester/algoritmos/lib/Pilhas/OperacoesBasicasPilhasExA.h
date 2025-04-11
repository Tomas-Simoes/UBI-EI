

typedef struct
{
  int numAluno;      // n�mero de aluno (chave): { 70000, �, 75000 }
  float notasMTP[2]; // notas dos mini-testes pr�ticos: [0.0, 2.0]
  float notasTE[2];  // notas dos testes escritos: [0.0, 8.0]
  int notaFinal;     // nota final, que � o valor arredondado da soma das 4 notas: { 0, �, 20 }
} INFOPilha;

/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

void mostrarElementoPilha(INFOPilha);

INFOPilha criarElementoPilha();

// compara��o de 2 elementos do tipo DADOSP, segundo o campo numAluno (chave)
// devolve -1 se primeiro < segundo, 0 se iguais, 1 se primeiro > segundo
int compararElementosPilha(INFOPilha, INFOPilha);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

void mostrarElementoPilha(INFOPilha X)
{
  printf("%d - ", X.numAluno);
  printf("%.2f - %.2f - ", X.notasMTP[0], X.notasMTP[1]);
  printf("%.2f - %.2f - ", X.notasTE[0], X.notasTE[1]);
  printf("%2d\n", X.notaFinal);
}

INFOPilha criarElementoPilha()
{
  INFOPilha X;
  float soma;
  X.numAluno = gerarNumeroInteiro(70000, 75000);
  X.notasMTP[0] = gerarNumeroReal(0.0, 2.0);
  X.notasMTP[1] = gerarNumeroReal(0.0, 2.0);
  X.notasTE[0] = gerarNumeroReal(0.0, 8.0);
  X.notasTE[1] = gerarNumeroReal(0.0, 8.0);
  soma = X.notasMTP[0] + X.notasMTP[1] + X.notasTE[0] + X.notasTE[1];
  X.notaFinal = (int)(soma + 0.5);
  return X;
}

// compara��o de 2 elementos do tipo DADOSP, segundo o campo numAluno (chave)
// devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
int compararElementosPilha(INFOPilha X, INFOPilha Y)
{
  if (X.numAluno > Y.numAluno)
    return 1;
  if (X.numAluno < Y.numAluno)
    return -1;
  return 0;
}

