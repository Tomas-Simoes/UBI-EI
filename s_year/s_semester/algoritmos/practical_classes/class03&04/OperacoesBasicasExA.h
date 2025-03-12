
typedef struct
{
  int numAluno;      // n�mero de aluno ({ 70000, �, 75000 })
  float notasMTP[2]; // notas dos mini-testes pr�ticos ([0.0, 2.0])
  float notasTE[2];  // notas dos testes escritos ([0.0, 8.0])
  int notaFinal;     // nota final ({ 0, �, 20 }): valor arredondado da soma das notas
} INFOLista;

/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

void mostrarElementoLista(INFOLista);

INFOLista criarElementoLista();

// compara��o de 2 elementos do tipo INFOLista, segundo o campo numAluno (chave)
// devolve -1 se primeiro < segundo, 0 se iguais, 1 se primeiro > segundo
int compararElementosLista(INFOLista, INFOLista);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

void mostrarElementoLista(INFOLista X)
{
  printf("%d - ", X.numAluno);
  printf("%.2f - %.2f - ", X.notasMTP[0], X.notasMTP[1]);
  printf("%.2f - %.2f - ", X.notasTE[0], X.notasTE[1]);
  printf("%2d\n", X.notaFinal);
}

INFOLista criarElementoLista()
{
  INFOLista X;
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

// compara��o de 2 elementos do tipo INFOLista, segundo o campo numAluno (chave)
//   devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
int compararElementosLista(INFOLista X, INFOLista Y)
{
  if (X.numAluno > Y.numAluno)
    return 1;
  if (X.numAluno < Y.numAluno)
    return -1;
  return 0;
}
