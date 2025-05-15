
#include <stdio.h>
#include <stdlib.h>

#include "../../lib/Aleatorio.h"
#include "../../lib/abp/OperacoesBasicasExABP.h"
#include "../../lib/abp/EADArvoreBinariaPesquisa.h"
#include "../../lib/abp/ABPorNiveis.h"
#include "OperacoesExABP.h"

int main()
{
  PNodoABP T;

  int height, levels;

  // Ex. 1
  T = criarABPAleatoria(0, 15);
  printf("Mostrar ABP por niveis:\n");
  mostrarPorNiveisABP(T);

  // Ex. 3
  height = alturaABP(T);
  levels = height + 1;

  printf("A ABP tem %d de altura e %d niveis\n", height, levels);

  // Ex. 4
  printf("Maior valor da arvore: ");
  mostrarElementoABP(maiorValorIt(T));

  printf("Maior valor da arvore recursivamente: ");
  mostrarElementoABP(maiorValorRec(T));

  // Ex. 6
  printf("Quantidade de elementos maiores que 73000: %d\n", contarElementos(T, 73000));

  // Ex. 13
  printf("Nivel da folha mais proxima: %d\n", nivelDaFolhaMaisProxima(T, 0));
  printf("Nivel da folha mais proxima (PROF): %d\n", nivelDaFolhaMaisProxima_PROF(T, 0));
  printf("Nivel da folha mais longe: %d", levels);

  // Ex. 15
}
