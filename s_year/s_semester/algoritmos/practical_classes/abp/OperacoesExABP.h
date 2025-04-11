#include <limits.h>
/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

PNodoABP criarABPAleatoria(int, int);

// Ex. 4
INFOABP maiorValorIt(PNodoABP T);
INFOABP maiorValorRec(PNodoABP T);

// Ex. 6
int contarElementos(PNodoABP T, int A);

// Ex. 13
int nivelDaFolhaMaisProxima(PNodoABP T, int level);
int nivelDaFolhaMaisProxima_PROF(PNodoABP T, int level);

// Ex. 15
/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

PNodoABP criarABPAleatoria(int A, int B)
{
  int k, N;
  INFOABP X;
  PNodoABP T;

  N = gerarNumeroInteiro(A, B);
  T = criarABP();
  k = 1;
  while (k <= N)
  {
    X = criarElementoABP();
    if (pesquisarABP(X, T) == NULL)
    {
      T = inserirABP(X, T);
      k = k + 1;
    }
  }
  return T;
}

INFOABP maiorValorIt(PNodoABP T)
{
  int highestRight;
  int highest = 0;

  while (T->Direita != NULL)
  {
    T = T->Direita;
  }

  return T->Elemento;
}

INFOABP maiorValorRec(PNodoABP T)
{
  if (T->Direita == NULL)
  {
    return T->Elemento;
  }

  return maiorValorRec(T->Direita);
}

int contarElementos(PNodoABP T, int A)
{
  if (T == NULL)
  {
    return 0;
  }

  if (T->Elemento.numAluno >= A)
  {
    return 1 + contarElementos(T->Direita, A) + contarElementos(T->Esquerda, A);
  }

  if (T->Elemento.numAluno < A)
  {
    return 0 + contarElementos(T->Direita, A);
  }
}

int nivelDaFolhaMaisProxima(PNodoABP T, int level)
{
  int levelEsq, levelDir;
  levelEsq = INT_MAX;
  levelDir = INT_MAX;

  if (T->Esquerda == NULL && T->Direita == NULL)
    return level;

  if (T->Esquerda != NULL)
    levelEsq = nivelDaFolhaMaisProxima(T->Esquerda, level + 1);

  if (T->Direita != NULL)
    levelDir = nivelDaFolhaMaisProxima(T->Direita, level + 1);

  return (levelEsq < levelDir) ? levelEsq : levelDir;
}

int nivelDaFolhaMaisProxima_PROF(PNodoABP T, int level)
{
  if (T->Esquerda == NULL && T->Direita == NULL)
    return level;

  if (T->Esquerda == NULL)
    return nivelDaFolhaMaisProxima(T->Direita, level + 1);

  if (T->Direita == NULL)
    return nivelDaFolhaMaisProxima(T->Esquerda, level + 1);

  int levelEsq = nivelDaFolhaMaisProxima(T->Esquerda, level + 1);
  int levelDir = nivelDaFolhaMaisProxima(T->Direita, level + 1);

  return (levelEsq < levelDir) ? levelEsq : levelDir;
}

PNodoABP removerMenorElemento(PNodoABP T)
{
  PNodoABP Aux, FatherAux;

  if (T->Esquerda == NULL)
  {
    Aux = T;
    T = T->Direita;
    Aux = libertarNodoABP(Aux);

    return T;
  }

  FatherAux = T;
  Aux = T->Esquerda;

  while (Aux->Esquerda != NULL)
  {
    FatherAux = Aux;
    Aux = Aux->Esquerda;
  }

  FatherAux->Esquerda = Aux->Direita;
}