// tipos de dados

struct NodoLista
{
  INFOLista Elemento;
  struct NodoLista *Prox;
};

typedef struct NodoLista *PNodoLista;

/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

// opera��es sobre um nodo (Nodo)

PNodoLista criarNodoLista(INFOLista);

PNodoLista libertarNodoLista(PNodoLista);

// Opera��es sobre uma EAD lista (PNodo)

PNodoLista criarLista();

PNodoLista libertarLista(PNodoLista);

int listaVazia(PNodoLista);

void mostrarListaInicio(PNodoLista);
void mostrarListaInicioRec(PNodoLista);

void mostrarListaFimRec(PNodoLista);

int pesquisarLista(INFOLista, PNodoLista);
int pesquisarListaRec(INFOLista, PNodoLista);

INFOLista consultarLista(INFOLista, PNodoLista);
INFOLista consultarListaRec(INFOLista, PNodoLista);

void atualizarLista(INFOLista, PNodoLista);

PNodoLista inserirListaInicio(INFOLista, PNodoLista);
PNodoLista inserirListaFim(INFOLista, PNodoLista);
// lista ordenada por ordem crescente
PNodoLista inserirListaOrdem(INFOLista, PNodoLista);

// remover elemento da lista (o elemento est� na lista)
PNodoLista removerLista(INFOLista, PNodoLista);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

// opera��es sobre um nodo (Nodo)

PNodoLista criarNodoLista(INFOLista X)
{
  PNodoLista P;
  P = (PNodoLista)malloc(sizeof(struct NodoLista));
  if (P == NULL)
    return NULL;
  P->Elemento = X;
  P->Prox = NULL;
  return P;
}

PNodoLista libertarNodoLista(PNodoLista P)
{
  P->Prox = NULL;
  free(P);
  P = NULL;
  return P;
}

// Opera��es sobre uma EAD lista (PNodo)

PNodoLista criarLista()
{
  PNodoLista L;
  L = NULL;
  return L;
}

// liberta todos os nodos da lista, devolvendo-a vazia
PNodoLista libertarLista(PNodoLista L)
{
  PNodoLista P;
  while (L != NULL)
  {
    P = L;
    L = L->Prox;
    P = libertarNodoLista(P);
  }
  return L;
}

int listaVazia(PNodoLista L)
{
  if (L == NULL)
    return 1;
  else
    return 0;
}

void mostrarListaInicio(PNodoLista L)
{
  PNodoLista P = L;
  while (P != NULL)
  {
    mostrarElementoLista(P->Elemento);
    P = P->Prox;
  }
}

void mostrarListaInicioRec(PNodoLista L)
{
  if (L != NULL)
  {
    mostrarElementoLista(L->Elemento);
    mostrarListaInicioRec(L->Prox);
  }
}

void mostrarListaFimRec(PNodoLista L)
{
  if (L != NULL)
  {
    mostrarListaFimRec(L->Prox);
    mostrarElementoLista(L->Elemento);
  }
}

int pesquisarLista(INFOLista X, PNodoLista L)
{
  while (L != NULL && compararElementosLista(L->Elemento, X) != 0)
    L = L->Prox;
  if (L == NULL)
    return 0;
  else
    return 1;
}

int pesquisarListaRec(INFOLista X, PNodoLista L)
{
  if (L == NULL)
    return 0;
  if (compararElementosLista(L->Elemento, X) == 0)
    return 1;
  return pesquisarListaRec(X, L->Prox);
}

// X est� na lista L
INFOLista consultarLista(INFOLista X, PNodoLista L)
{
  PNodoLista P = L;
  while (P != NULL && compararElementosLista(P->Elemento, X) != 0)
    P = P->Prox;
  return P->Elemento;
}

// X est� na lista L
INFOLista consultarListaRec(INFOLista X, PNodoLista L)
{
  // caso base/terminal
  if (compararElementosLista(L->Elemento, X) == 0)
    return L->Elemento;
  // caso geral
  return consultarListaRec(X, L->Prox);
}

// atualiza os dados do elemento da lista com a chave X
//  existe um elemento na lista com a chave X
void atualizarLista(INFOLista X, PNodoLista L)
{
  PNodoLista P = L;
  while (compararElementosLista(P->Elemento, X) != 0)
    P = P->Prox;
  P->Elemento = X;
}

PNodoLista inserirListaInicio(INFOLista X, PNodoLista L)
{
  PNodoLista P;
  P = criarNodoLista(X);
  if (P == NULL)
    return L;
  P->Prox = L;
  L = P;
  return L;
}

PNodoLista inserirListaFim(INFOLista X, PNodoLista L)
{
  PNodoLista Fim, P;
  P = criarNodoLista(X); // P aponta para o novo nodo (com X)
  if (P == NULL)
    return L;
  if (L == NULL) // lista vazia, logo X � o �nico elemento da lista
    return P;
  Fim = L;
  while (Fim->Prox != NULL) // marcar o elemento do fim de L
    Fim = Fim->Prox;
  Fim->Prox = P; // ligar �ltimo nodo da lista L ao novo nodo (com o X)
  return L;
}

// assume-se que a lista est� ordenada por ordem crescente

PNodoLista inserirListaOrdem(INFOLista X, PNodoLista L)
{
  PNodoLista Ant, P, Aux;
  P = criarNodoLista(X);
  if (P == NULL)
    return L;
  if (L == NULL)
  {           // o novo nodo � o �nico da lista
    L = P;    // bastava colocar:
    return L; //   return P;
  }
  // procurar pelo nodo que ser� antecessor do novo nodo (com X)
  Ant = NULL;
  Aux = L;
  while (Aux != NULL && compararElementosLista(Aux->Elemento, X) < 0)
  {
    Ant = Aux;
    Aux = Aux->Prox;
  }
  if (Ant == NULL)
  { // inserir o novo nodo no in�cio de L
    P->Prox = L;
    L = P;
    return L;
  }
  // inserir o novo nodo depois do in�cio
  P->Prox = Ant->Prox;
  Ant->Prox = P;
  return L;
}

// remover X da lista L, em que X est� na lista
PNodoLista removerLista(INFOLista X, PNodoLista L)
{
  PNodoLista P, Ant;

  // verificar se o elemento a remover est� na cabe�a da lista
  if (compararElementosLista(L->Elemento, X) == 0)
  {
    P = L;
    L = L->Prox;
    P = libertarNodoLista(P);
    return L;
  }

  // procurar o antecessor do elemento a remover (que n�o est� na cabe�a)
  Ant = L;
  while (compararElementosLista(Ant->Prox->Elemento, X) != 0)
    Ant = Ant->Prox;
  P = Ant->Prox;
  Ant->Prox = P->Prox; // ou (= Ant->Prox)->Prox
  P = libertarNodoLista(P);
  return L;
}
