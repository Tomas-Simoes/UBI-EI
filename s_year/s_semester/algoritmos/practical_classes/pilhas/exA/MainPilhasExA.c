#include <stdio.h>
#include <stdlib.h>

#include "../../../lib/Aleatorio.h"
#include "OperacoesBasicasPilhasExA.h"
#include "EADPilha.h"
#include "OperacoesPilhasExA.h"

int elementoMaisProx(PNodoPilha *S)
{
  int result;
  PNodoPilha aux;

  aux = criarPilha();

  while (pilhaVazia(*S) == 0)
  {
    if (topo(*S).numAluno > 73000)
    {
      result = topo(*S).numAluno;
      break;
    }
    aux = push(topo(*S), aux);
    *S = pop(*S);
  }

  while (pilhaVazia(aux) == 0)
  {
    *S = push(topo(aux), *S);
    aux = pop(aux);
  }

  return result;
}

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

    printf("O elemento mais prox e %d\n", elementoMaisProx(&Pilha));
  }

  printf("\nPilha Atual: \n");
  mostrarPilha(Pilha);

  printf("\nPilha com primeiro e ultimo trocado: \n");
  // swap first and last
  swapFirstLast(&Pilha);
  mostrarPilha(Pilha);
}
