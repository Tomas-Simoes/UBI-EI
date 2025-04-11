
// tipos de dados

struct NodoPilha {
  INFOPilha  Elemento;
  struct NodoPilha *Ant;
};

typedef struct NodoPilha *PNodoPilha;

/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

// Opera��es sobre um nodo (NodoPilha)

PNodoPilha criarNodoPilha (INFOPilha);

PNodoPilha libertarNodoPilha (PNodoPilha);

// Opera��es sobre uma Pilha (PNodoPilha)

PNodoPilha criarPilha ();

int pilhaVazia (PNodoPilha);

PNodoPilha push (INFOPilha, PNodoPilha);

PNodoPilha pop (PNodoPilha);

INFOPilha topo (PNodoPilha);


/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

// Opera��es sobre um nodo (NodoPilha)

PNodoPilha criarNodoPilha (INFOPilha X)
{
  PNodoPilha P;
  P = (PNodoPilha) malloc(sizeof(struct NodoPilha));
  if (P == NULL)
    return NULL;
  P->Elemento = X;
  P->Ant = NULL;
  return P;
}

PNodoPilha libertarNodoPilha (PNodoPilha P)
{
  P->Ant = NULL;
  free(P);
  P = NULL;
  return P;
}

// Opera��es sobre uma EAD Pilha (PNodoPilha)

PNodoPilha criarPilha ()
{
  PNodoPilha S;
  S = NULL;
  return S;
}

int pilhaVazia (PNodoPilha S)
{
  if (S == NULL)
    return 1;
  else
    return 0;
}

PNodoPilha push (INFOPilha X, PNodoPilha S)
{
  PNodoPilha P;
  P = criarNodoPilha(X);
  if (P == NULL)
    return S;
  P->Ant = S;
  S = P;
  return S;
}

PNodoPilha pop (PNodoPilha S)
{
  PNodoPilha P;
  P = S;
  S = S->Ant;
  P = libertarNodoPilha(P);
  return S;
}

INFOPilha topo (PNodoPilha S)
{
  return S->Elemento;
}




