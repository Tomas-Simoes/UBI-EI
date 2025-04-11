
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

PNodoFila criarFilaAleatoria(int A, int B) {
  int size = gerarNumeroInteiro( A, B);

  PNodoFila F = criarFila();

  for (int i = 0; i < size; i++)
  {
    INFOFila el = criarElementoFila();
    F = juntar(el, F);
  }
  
  return F;
}