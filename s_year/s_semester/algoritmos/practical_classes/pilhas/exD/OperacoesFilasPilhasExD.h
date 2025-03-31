
/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

// opera��o apenas para controlo:
//   - n�o faz parte da EAD Fila
//   - mostra a Fila da frente para a cauda
void mostrarFila(PNodoFila);

PNodoFila criarFilaAleatoria(int A, int B);
PNodoFila inverterFila(PNodoFila F);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

// opera��o apenas para controlo:
//   - n�o faz parte da EAD Fila
//   - mostra a Fila da frente para a cauda
void mostrarFila(PNodoFila Q)
{
  PNodoFila P = Q;
  while (P != NULL)
  {
    mostrarElementoFila(P->Elemento);
    P = P->Seg;
  }
}

PNodoFila criarFilaAleatoria(int A, int B)
{
  PNodoFila F;
  int N, i;
  INFOFila X;

  N = gerarNumeroInteiro(A, B);
  F = criarFila();

  for (i = 0; i < N; i++)
  {
    X = criarElementoFila();
    F = juntar(X, F);
  }

  return F;
}

PNodoFila inverterFila(PNodoFila F)
{
  PNodoPilha P;
  P = criarPilha;

  while (filaVazia(F) == 0)
  {
    P = push(frente(F), P);
    F = remover(F);
  }

  while (pilhaVazia(P) == 0)
  {
    F = juntar(topo(P), F);
    P = pop(P);
  }

  return F;
}