
/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

// opera��o apenas para controlo
//   - n�o faz parte da EAD Pilha
//   - mostra a Pilha do topo para o fundo
void mostrarPilha(PNodoPilha);
PNodoPilha criarPilhaAleatoria(int A, int B);
INFOPilha fundoPilha(PNodoPilha *S);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

// opera��o apenas para controlo
//   - n�o faz parte da EAD Pilha
//   - mostra a Pilha do topo para o fundo
void mostrarPilha(PNodoPilha S)
{
  PNodoPilha P = S;
  int i = 0;

  while (P != NULL)
  {
    mostrarElementoPilha(P->Elemento);
    P = P->Ant;

    i++;
  }
}

PNodoPilha criarPilhaAleatoria(int A, int B)
{
  int tam = gerarNumeroInteiro(A, B);

  PNodoPilha P = NULL;
  INFOPilha el;

  for (int i = 0; i < tam; i++)
  {
    el = criarElementoPilha();
    P = push(el, P);
  }

  return P;
}

int mostrarSegundo(PNodoPilha *P, INFOPilha *el)
{
  if (*P == NULL)
  {
    return -1;
  }

  *el = topo(*P);
  *P = pop((*P));

  if (*P == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

INFOPilha fundoPilha(PNodoPilha *S)
{
  INFOPilha el;
  PNodoPilha Aux;

  Aux = criarPilha();

  while (pilhaVazia(*S) == 0)
  {
    Aux = push(topo(*S), Aux);
    *S = pop(*S);
  }

  el = topo(Aux);

  while (pilhaVazia(Aux) == 0)
  {
    *S = push(topo(Aux), *S);
    Aux = pop(Aux);
  }

  return el;
}