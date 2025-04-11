#include <stdlib.h>
#include <stdio.h>

#include "../lib/Aleatorio.h"
#include "../lib/Pilhas/OperacoesBasicasPilhasExA.h"
#include "../lib/Pilhas/EADPilha.h"

#include "../lib/AB/OperacoesBasicasExAB.h"
#include "../lib/AB/EADArvoreBinaria.h"
#include "../lib/AB/ABPorNiveis.h"
#include "../lib/AB/OperacoesExAB.h"

#include "../lib/Listas/OperacoesBasicasExA.h"
#include "../lib/Listas/EADLista.h"
#include "../lib/Listas/OperacoesExA.h"

PNodoPilha criarPilhaAleatoria(int A, int B);
void mostrarPilha(PNodoPilha S);

int closestValueToTop(PNodoPilha S);

int higherValue(PNodoAB T);
int higherListValue(PNodoLista L);

PNodoLista removerSegundoElemento(PNodoLista L, int N);


int main(){
    // Pilhas    
    PNodoPilha Stack = criarPilhaAleatoria(3, 15);

    printf("Stack atual: \n");
    mostrarPilha(Stack);

    printf("\nValor mais proximo do topo maior que 7000: %d\n",  closestValueToTop(Stack));

    printf("Stack atual: \n");
    mostrarPilha(Stack);

    // Arvores
    PNodoAB Tree = gerarABAleatoria(3, 15);
    printf("\n\nAB Atual: \n");
    mostrarPorNiveisAB(Tree);

    printf("\nMaior valor de AB: %d\n", higherValue(Tree));

    // Listas
    PNodoLista List = criarListaAleatoria(3, 15);
    printf("\n\nLista Atual: \n");
    mostrarListaInicio(List);

    printf("\n Maior valor da lista: %d\n", higherListValue(List));

    printf("\n Lista apos remocao do segundo elemento > 71000: \n");
    mostrarListaInicio(removerSegundoElemento(List, 71000));
}

int closestValueToTop(PNodoPilha S) {
    PNodoPilha Aux = criarPilha();
    int num = -1;
    
    while (S != NULL)
    {   
        num = topo(S).numAluno;

        // na freq seria < 0
        if (num > 74000) {
            break;
        }
        Aux = push(topo(S), Aux);
        S = pop(S);
    }
    
    while (Aux != NULL)
    {
        S = push(topo(Aux), S);
        Aux = pop(Aux);
    }
    
    return num;
}

int higherValue(PNodoAB T) {
    int higher, higherLeft, higherRight;
    
    higher = T->Elemento.numAluno;

    if(T->Direita == NULL && T->Esquerda == NULL) {
        return higher;
    }

    if(T->Esquerda != NULL) {
        higherLeft = higherValue(T->Esquerda);
        
        if(higherLeft > higher) higher = higherLeft;
    }

    if(T->Direita != NULL) {
        higherRight = higherValue(T->Direita);

        if(higherRight > higher) higher = higherRight;
    }

    return higher;
}

int higherListValue(PNodoLista L) {
    int higher ;

    higher = L->Elemento.numAluno;

    while (L != NULL)
    {
        if(L->Elemento.numAluno > higher) higher = L->Elemento.numAluno;

        L = L->Prox;
    }

    return higher;
}

PNodoLista removerSegundoElemento(PNodoLista L, int N) {
    PNodoLista Head, Aux;
    int is_second = 0;

    Head = L; 

    while (L != NULL)
    {
        if(L->Elemento.numAluno > N) {
            if(is_second == 1) {
                Aux->Prox = L->Prox;
                libertarNodoLista(L);

                return Head;
            } else is_second++;
        }

        Aux = L;
        L = L->Prox;
    }

    return Head;
}

// util func
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


