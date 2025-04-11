
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../lib/Aleatorio.h"
#include "OperacoesBasicasExAB.h"
#include "EADArvoreBinaria.h"
#include "ABPorNiveis.h"
#include "OperacoesExAB.h"

int main()
{
  PNodoAB T;

  T = gerarABAleatoria(10, 15);
  printf("Mostrar em ordem: \n");
  mostrarEmOrdemAB(T);

  printf("Mostrar em pre-ordem: \n");
  mostrarPreOrdemAB(T);

  printf("Mostrar em pos-ordem: \n");
  mostrarPosOrdemAB(T);

  printf("Mostrar por niveis: \n");
  mostrarPorNiveisAB(T);

  printf("Tamanho da arvore: %d\n", quantidadeDeElementos(T));

  printf("Media de notas finais: %.2f\n", mediaNotaFinal(T));

  printf("Maior nota final v1: %d\n", maiorNotaFinal(T));

  if (ABVazia(T) == 0)
    printf("Maior nota final v2: %d\n", maiorNotaFinal2(T));

  printf("\n\nQuantidade de nós com 1 filho: %d\n", quantidadeNos1Filho(T));

  printf("\nNivel do elemento: %d", nivelDoElemento(T, (((T->Direita)->Direita)->Elemento), 0));
}
