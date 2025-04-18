
struct NodoAB {
	INFOAB  Elemento;
	struct NodoAB *Esquerda;
	struct NodoAB *Direita;
};

typedef struct NodoAB *PNodoAB;

/* ------------------------------------------------------- */
/* ---- protótipos/headers das funções da biblioteca ----- */
/* ------------------------------------------------------- */

// Operações sobre o Nodo

PNodoAB criarNodoAB(INFOAB);

PNodoAB libertarNodoAB(PNodoAB);

// Operações sobre a EAD Árvore Binária

PNodoAB criarAB();

PNodoAB destruirAB(PNodoAB);

int ABVazia(PNodoAB);

void mostrarEmOrdemAB (PNodoAB);
void mostrarPreOrdemAB (PNodoAB);
void mostrarPosOrdemAB (PNodoAB);

int alturaAB (PNodoAB);

PNodoAB pesquisarAB (INFOAB, PNodoAB);

void atualizarElementoAB (INFOAB, INFOAB, PNodoAB);

// inserir de forma que fique o mais possível equilibrada
PNodoAB inserirPorAlturaAB (INFOAB, PNodoAB);

// remover um elemento de uma árvore
//  X está na árvore binária T
PNodoAB removerAB (INFOAB, PNodoAB);

/* ------------------------------------------------------- */
/* -------------- implementação das funções -------------- */
/* ------------------------------------------------------- */

// Operações sobre o Nodo

PNodoAB criarNodoAB(INFOAB X)
{
  PNodoAB P;
  P = (PNodoAB) malloc(sizeof(struct NodoAB));
  if (P == NULL)
    return  NULL;
  P->Elemento = X;
  P->Esquerda = NULL;
  P->Direita = NULL;
  return P;
}

PNodoAB libertarNodoAB(PNodoAB P)
{
  P->Esquerda = NULL;
  P->Direita = NULL;
  free(P);
  P = NULL;
  return P;
}

// Operações sobre a EAD Árvore Binária

PNodoAB criarAB()
{
  PNodoAB T;
  T = NULL;
  return T;
}

PNodoAB destruirAB(PNodoAB T)
{
  if (T == NULL) 
    return NULL;
  T->Esquerda = destruirAB(T->Esquerda);
  T->Direita = destruirAB(T->Direita);
  T = libertarNodoAB(T);
  return T;
}

int ABVazia(PNodoAB T)
{
  if (T == NULL)
    return 1;
  else
    return 0;
}

void mostrarEmOrdemAB (PNodoAB T)
{
  if (T != NULL){
    mostrarEmOrdemAB(T->Esquerda);
    mostrarElementoAB(T->Elemento);
    mostrarEmOrdemAB(T->Direita);
  }
}

void mostrarPreOrdemAB (PNodoAB T)
{
  if (T != NULL){
    mostrarElementoAB(T->Elemento);
    mostrarPreOrdemAB(T->Esquerda);
    mostrarPreOrdemAB(T->Direita);
  }
}

void mostrarPosOrdemAB (PNodoAB T)
{
  if (T != NULL){
    mostrarPosOrdemAB(T->Esquerda);
    mostrarPosOrdemAB(T->Direita);
    mostrarElementoAB(T->Elemento);
  }
}

int alturaAB (PNodoAB T)
{
  int  altEsq, altDir;
  if (T == NULL)
    return -1;
  altEsq = alturaAB(T->Esquerda);
  altDir = alturaAB(T->Direita);
  if (altEsq > altDir)
    return altEsq + 1;	// altura da esquerda + raiz
  else
    return altDir + 1;	// altura da direita + raiz
}

PNodoAB pesquisarAB (INFOAB X, PNodoAB T)
{
  PNodoAB P;
  if (T == NULL)
    return NULL;
  if (compararElementosAB(X, T->Elemento) == 0)  // X = T->Elemento
    return T;
  P = pesquisarAB(X, T->Esquerda);
  if (P != NULL)
    return P;
  return pesquisarAB(X, T->Direita);
}

void atualizarElementoAB (INFOAB X, INFOAB Y, PNodoAB T)
{
  PNodoAB P;
  P = pesquisarAB(X, T);
  if (P != NULL)
    P->Elemento = Y;
}

// inserir de forma que fique o mais possível equilibrada

PNodoAB inserirPorAlturaAB (INFOAB X, PNodoAB T)
{
  if (T == NULL){
    T = criarNodoAB(X);
    return T;
  }
  if (alturaAB(T->Esquerda) > alturaAB(T->Direita))
    T->Direita = inserirPorAlturaAB(X, T->Direita);
  else
    T->Esquerda = inserirPorAlturaAB(X, T->Esquerda);
  return T;
}
 
 // remover um elemento de uma árvore
    
PNodoAB procurarFolhaAB (PNodoAB T, INFOAB *X)
{
  if (T->Esquerda == NULL && T->Direita == NULL){
    *X = T->Elemento;
    T = libertarNodoAB(T);
    return T;
  }
  if (alturaAB(T->Esquerda) > alturaAB(T->Direita))
    T->Esquerda = procurarFolhaAB(T->Esquerda, X);
  else
    T->Direita = procurarFolhaAB(T->Direita, X);
  return T;
}

PNodoAB removerNodoAB (PNodoAB T)
{
  PNodoAB P;
  INFOAB  X;
  if (T->Esquerda == NULL && T->Direita == NULL){   // T é uma folha
    T = libertarNodoAB(T);
    return T;
  }
  if (T->Esquerda == NULL){   //  só um filho direito 
    P = T;
    T = T->Direita;
    P = libertarNodoAB(P);
    return T;
  }
  if (T->Direita == NULL){     // só um filho esquerdo
    P = T;
    T = T->Esquerda;
    P = libertarNodoAB(P);
    return T;
  }
  // 2 filhos: remover a folha escolhida e copiar a sua informação
  T = procurarFolhaAB(T, &X);
  T->Elemento = X;
  return T;
}

//  X está na árvore binária T
PNodoAB removerAB (INFOAB X, PNodoAB T)
{
  PNodoAB P;
  if (compararElementosAB(T->Elemento, X) == 0){
    T = removerNodoAB(T);
    return T;
  }
  P = pesquisarAB(X, T->Esquerda);
  if (P != NULL)
    T->Esquerda = removerAB(X, T->Esquerda);
  else
    T->Direita = removerAB(X, T->Direita);
  return T;
}


