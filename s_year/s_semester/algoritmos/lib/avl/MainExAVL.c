
#include <stdio.h>
#include <stdlib.h>

#include "OperacoesBasicasExAVL.h"
#include "EADArvoreBinariaPesquisaAVL.h"
#include "AVLPorNiveis.h"

int main()
{
  PNodoAVL T;
  INFOAVL X;
  int opcao, N;
  
  T = criarAVL();
  do{
    printf("\nINSERIR[1], REMOVER[2] e TERMINAR[< 0]: ");
    scanf("%d", &opcao);
    switch (opcao){
      case 1:
      	printf("INSERIR ELEMENTO.\n");
        X = criarElementoAVL();
        if (pesquisarAVL(X, T) == NULL){
          T = inserirAVL(T, X);
          mostrarAVLPorNiveis(T);
          printf("\n");
        }
        else
          printf("Elemento existente!\n");
        break;
      case 2:
      	printf("REMOVER ELEMENTO.\n");
        X = criarElementoAVL();
        if (pesquisarAVL(X, T) != NULL){
          T = removerAVL(T, X);
          mostrarAVLPorNiveis(T);
          printf("\n");
        }
        else
          printf("Elemento nao existente!\n");
        break;
      default:
      	break;
	}
  }while (opcao > 0);
 
  return 1;
  
}
