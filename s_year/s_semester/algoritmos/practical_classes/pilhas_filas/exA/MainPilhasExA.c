#include <stdio.h>
#include <stdlib.h>

#include "../../../lib/Aleatorio.h"
#include "OperacoesBasicasPilhasExA.h"
#include "EADPilha.h"
#include "OperacoesPilhasExA.h"

int main()
{
  PNodoPilha Pilha;
  INFOPilha secElemento;

  // Ex. 1
  printf("Pilha atual: \n");
  Pilha = criarPilhaAleatoria(1, 10);
  mostrarPilha(Pilha);

  // Ex. 7
  INFOPilha X;
  if (pilhaVazia(Pilha) == 0)
  {
    X = fundoPilha(&Pilha);

    printf("\nFundo da pilha é: ");
    mostrarElementoPilha(X);
  }

  printf("\nPilha Atual: \n");
  mostrarPilha(Pilha);

  printf("\nPilha com primeiro e ultimo trocado: \n");
  // swap first and last
  swapFirstLast(&Pilha);
  mostrarPilha(Pilha);
}
