
// bibliotecas exclusivas desta biblioteca

typedef PNodoAVL INFOFila;   // INFOFila = PNodoAVL

#include "EADFila.h"

/* ------------------------------------------------------- */
/* ---- protótipos/headers das funções da biblioteca ----- */
/* ------------------------------------------------------- */

void mostrarAVLPorNiveis (PNodoAVL);


/* ------------------------------------------------------- */
/* -------------- implementação das funções -------------- */
/* ------------------------------------------------------- */

void mostrarAVLPorNiveis (PNodoAVL T){
  PNodoFila Q;
  PNodoAVL  P;
  int niveis, k = 0;
  
  if (AVLVazia(T))
    return;
  niveis = alturaAVL(T) + 1;
  Q = criarFila();
  Q = juntar(T, Q);
  Q = juntar(NULL, Q);
  printf("Legenda: nodo-nivel[pai]\n");
  printf("Nivel %1d: %2d-%1d\n", k, T->Elemento, T->Altura);
  k++;
  printf("Nivel %1d: ", k);
  while (!filaVazia(Q)){
    P = frente(Q);
    Q = remover(Q);
    if (P == NULL){
      k++;
      if (k == niveis){
        printf("\n");
        return;
      }
      printf("\nNivel %1d: ", k);
      if (!filaVazia(Q))
        Q = juntar(NULL, Q);
    }
    else{
      // mostrarElemento(P->Elemento);
      if (P->Esquerda != NULL)
        printf("%2d-%1d[%2d] # ", P->Esquerda->Elemento, P->Esquerda->Altura, P->Elemento);  // [pai]
      else
        printf("    [%2d] # ", P->Elemento);
      if (P->Direita != NULL)
        printf("%2d-%1d[%2d] # ", P->Direita->Elemento, P->Direita->Altura, P->Elemento);
      else
        printf("    [%2d] # ", P->Elemento);
      if (P->Esquerda != NULL)
        Q = juntar(P->Esquerda, Q);
      if (P->Direita != NULL)
        Q = juntar(P->Direita, Q);
    }
  }
  printf("\n");
}


