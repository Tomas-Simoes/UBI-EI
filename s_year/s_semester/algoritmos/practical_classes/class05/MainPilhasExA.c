
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/Aleatorio.h"
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

  printf("test\n\n");

  /*
  // Ex. 2
  int existe = mostrarSegundo(&Pilha, &secElemento);

  switch (existe)
  {
  case -1:
    printf("Pilha esta vazia.");
    break;
  case 0:
    printf("Não existe segundo elemento.");
    break;
  default:
    printf("O segundo elemento é: ");
    mostrarElementoPilha(secElemento);

    printf("A nova pilha é: \n");
    mostrarPilha(Pilha);
    break;
  }
  */
}
