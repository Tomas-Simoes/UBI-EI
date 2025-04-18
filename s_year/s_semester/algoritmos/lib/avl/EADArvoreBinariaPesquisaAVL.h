
// tipos de dados

struct NodoAVL {
  INFOAVL Elemento;
  int     Altura;
  struct NodoAVL *Esquerda;
  struct NodoAVL *Direita;
};

typedef struct NodoAVL *PNodoAVL;


/* ------------------------------------------------------- */
/* ---- protótipos/headers das funções da biblioteca ----- */
/* ------------------------------------------------------- */

// Operações sobre o Nodo

PNodoAVL criarNodoAVL (INFOAVL);

PNodoAVL libertarNodoAVL (PNodoAVL);

// Operações sobre a EAD ABP do tipo AVL

PNodoAVL criarAVL ();

PNodoAVL destruirAVL (PNodoAVL);

int AVLVazia (PNodoAVL);

void mostrarEmOrdemAVL (PNodoAVL);
void mostrarPreOrdemAVL (PNodoAVL);
void mostrarPosOrdemAVL (PNodoAVL);

int alturaAVL (PNodoAVL);

PNodoAVL pesquisarAVL (INFOAVL, PNodoAVL);

void atualizarElementoAVL (INFOAVL, INFOAVL, PNodoAVL);

PNodoAVL inserirAVL (PNodoAVL, INFOAVL);

// T não vazia e X pertence a T
PNodoAVL removerAVL (PNodoAVL, INFOAVL);


/* ------------------------------------------------------- */
/* -------------- implementação das funções -------------- */
/* ------------------------------------------------------- */

// Operações sobre o Nodo

PNodoAVL criarNodoAVL (INFOAVL X)
{
  PNodoAVL P;
  P = (PNodoAVL) malloc(sizeof(struct NodoAVL));
  if (P == NULL)
    return NULL;
  P->Elemento = X;
  P->Altura = 0;
  P->Esquerda = NULL;
  P->Direita = NULL;
  return P;
}

PNodoAVL libertarNodoAVL (PNodoAVL P)
{
  P->Esquerda = NULL;
  P->Direita = NULL;
  free(P);
  P = NULL;
  return P;
}

// Operações sobre a EAD ABP do tipo AVL

PNodoAVL criarAVL ()
{ 
  PNodoAVL T;
  T = NULL;
  return T;
}

PNodoAVL destruirAVL (PNodoAVL T)
{
  if (T == NULL) 
    return NULL;
  T->Esquerda = destruirAVL(T->Esquerda);
  T->Direita = destruirAVL(T->Direita);
  T = libertarNodoAVL(T);
  return T;
}

int AVLVazia (PNodoAVL T)
{
  if (T == NULL)
    return 1;
  return 0;
}

void mostrarEmOrdemAVL (PNodoAVL T) 
{
  if (T != NULL){
    mostrarEmOrdemAVL(T->Esquerda);
    mostrarElementoAVL(T->Elemento);
    mostrarEmOrdemAVL(T->Direita);
  }
}

void mostrarPreOrdemAVL (PNodoAVL T) 
{
  if (T != NULL){
    mostrarElementoAVL(T->Elemento);
    mostrarPreOrdemAVL(T->Esquerda);
    mostrarPreOrdemAVL(T->Direita);
  }
}

void mostrarPosOrdemAVL (PNodoAVL T) 
{
  if (T != NULL){
    mostrarPosOrdemAVL(T->Esquerda);
    mostrarPosOrdemAVL(T->Direita);
    mostrarElementoAVL(T->Elemento);
  }
}

int alturaAVL (PNodoAVL T){
	if (T == NULL)
		return -1;
	return T->Altura;
}

// Igual ao pesquisar ABP: 
//   NULL, se não existe 
//   ponteiro para o nodo, se existe
PNodoAVL pesquisarAVL (INFOAVL X, PNodoAVL T)
{
  if (T == NULL)
    return NULL;
  if (compararElementosAVL(X, T->Elemento) == 0)    // X = T->Elemento)
    return T;
  if (compararElementosAVL(X, T->Elemento) == -1)   // X < T->Elemento)
    return pesquisarAVL(X, T->Esquerda);
  else                                              // X > T->Elemento)
    return pesquisarAVL(X, T->Direita);
}

void atualizarElementoAVL (INFOAVL X, INFOAVL Y, PNodoAVL T)
{
  PNodoAVL P;
  P = pesquisarAVL(X,T);
  if (P != NULL){
    T = removerAVL(T,X);
    T = inserirAVL(T,Y);
  }
}

// inserir elemento numa AVL e remover elemento duma AVL

int atualizarAlturaNodo (PNodoAVL T)
{
  int altEsq, altDir;
  if (T == NULL)
    return -1;
  altEsq = alturaAVL(T->Esquerda);
  altDir = alturaAVL(T->Direita);
  if (altEsq > altDir)
    return altEsq + 1;
  else
    return altDir + 1;
}

PNodoAVL rotacaoSimplesEsquerda (PNodoAVL P)
{
  int altEsq, altDir;
  PNodoAVL nodoAux; 
  nodoAux = P->Direita;
  P->Direita = nodoAux->Esquerda;
  nodoAux->Esquerda = P;
  // atualizar a altura dos nodos envolvidos na rotação
  altEsq = alturaAVL(P->Esquerda);
  altDir = alturaAVL(P->Direita);
  if (altEsq > altDir)
    P->Altura = altEsq + 1;
  else
    P->Altura = altDir + 1;
  // atualizar a altura do nodo nodoAux (envolvido na rotação)
  altEsq = alturaAVL(P);
  altDir = alturaAVL(nodoAux->Direita);
  if (altEsq > altDir)
    nodoAux->Altura = altEsq + 1;
  else
    nodoAux->Altura = altDir + 1;
  return nodoAux;
}

PNodoAVL rotacaoSimplesDireita (PNodoAVL P)
{
  int altEsq, altDir;
  PNodoAVL nodoAux;
  nodoAux = P->Esquerda;
  P->Esquerda = nodoAux->Direita;
  nodoAux->Direita = P;
  // atualizar a altura dos nodos envolvidos na rotação
  altEsq = alturaAVL(P->Esquerda);
  altDir = alturaAVL(P->Direita);
  if (altEsq > altDir)
    P->Altura = altEsq + 1;
  else
    P->Altura = altDir + 1;
  // atualizar a altura do nodoAux (envolvido na rotação)
  altEsq = alturaAVL(nodoAux->Esquerda);
  altDir = alturaAVL(P);
  if (altEsq > altDir)
    nodoAux->Altura = altEsq + 1;
  else
    nodoAux->Altura = altDir + 1;
  return nodoAux;
}

PNodoAVL rotacaoDuplaEsquerda (PNodoAVL P)
{
  P->Direita = rotacaoSimplesDireita(P->Direita);
  P = rotacaoSimplesEsquerda(P);
  return P;
}

PNodoAVL rotacaoDuplaDireita (PNodoAVL P)
{
  P->Esquerda = rotacaoSimplesEsquerda(P->Esquerda);
  P = rotacaoSimplesDireita(P);
  return P;
}

PNodoAVL equilibrarAVL (PNodoAVL T)
{
  int altEsq, altDir;
  if (T == NULL)
    return T;
  altEsq = alturaAVL(T->Esquerda);
  altDir = alturaAVL(T->Direita);
  if (altEsq - altDir == 2){  // subárvore esquerda desequilibrada
    altEsq = alturaAVL(T->Esquerda->Esquerda);
    altDir = alturaAVL(T->Esquerda->Direita);
    if (altEsq > altDir)
      T = rotacaoSimplesDireita(T);
    else
      T = rotacaoDuplaDireita(T);  // esquerda --> direita
  }
  else 
    if (altDir - altEsq == 2){  // subárvore direita desequilibrada
      altEsq = alturaAVL(T->Direita->Esquerda);
      altDir = alturaAVL(T->Direita->Direita);
      if (altDir > altEsq)
        T = rotacaoSimplesEsquerda(T);
      else
        T = rotacaoDuplaEsquerda(T);  // direita --> esquerda
    }
  return T;
}

// X não existe em T
PNodoAVL inserirAVL (PNodoAVL T, INFOAVL X)
{
  if (T == NULL){
    T = criarNodoAVL(X);
    return T;
  }
  if (compararElementosAVL(T->Elemento, X) == 1)  // T->Elemento > X
    T->Esquerda = inserirAVL(T->Esquerda, X);
  else
    T->Direita = inserirAVL(T->Direita, X);
  T->Altura = atualizarAlturaNodo(T);
  T = equilibrarAVL(T);  // reequilibrar a árvore
  return T;
}

// elemento mais à esquerda da subárvore direita
PNodoAVL substituirNodoMinAVL (PNodoAVL T, INFOAVL *X)
{
  PNodoAVL  NodoAux = T;

  if (T->Esquerda == NULL){
    *X = T->Elemento;
    T = T->Direita;
    NodoAux = libertarNodoAVL(NodoAux);
  }
  else
    T->Esquerda = substituirNodoMinAVL(T->Esquerda, X);
    
  if (T != NULL){
    T->Altura = atualizarAlturaNodo(T);
    T = equilibrarAVL(T);
  }
  
  return T;
}

PNodoAVL removerNodoAVL (PNodoAVL T)
{
  PNodoAVL  NodoAux = T;
  INFOAVL X;
  if (T->Esquerda == NULL  && T->Direita == NULL)  // remover uma folha
    T = libertarNodoAVL(T);
  else
    if (T->Esquerda == NULL){  // só subárvore direita
      T = T->Direita;
      NodoAux = libertarNodoAVL(NodoAux);
    }
    else
      if (T->Direita == NULL){  // só subárvore esquerda
        T = T->Esquerda;
        NodoAux = libertarNodoAVL(NodoAux);
      }
      else{  // 2 subárvores não vazias: 
        //  substituir pelo menor elemento da subárvore direita
        T->Direita = substituirNodoMinAVL(T->Direita, &X);  //->Elemento);
        T->Elemento = X;
      }
  if (T != NULL){
    T->Altura = atualizarAlturaNodo(T);
    T = equilibrarAVL(T);  // reequilibrar a árvore
  }
  return T;
}

// remover um elemento de uma AVL:
//   T não vazia e X pertence a T
PNodoAVL removerAVL (PNodoAVL T, INFOAVL X)
{
  if (compararElementosAVL(T->Elemento, X) == 0){
    T = removerNodoAVL(T);
    return T;
  }
  if (compararElementosAVL(T->Elemento, X) == 1)
    T->Esquerda = removerAVL(T->Esquerda, X);
  else
    T->Direita = removerAVL(T->Direita, X);
    
  if (T != NULL){
    T->Altura = atualizarAlturaNodo(T);
    T = equilibrarAVL(T);  // reequilibrar a árvore
  }
  return T;
}


