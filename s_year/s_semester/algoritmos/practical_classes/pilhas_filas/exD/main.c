
#include <stdio.h>
#include <stdlib.h>

#include "Aleatorio.h"
#include "OperacoesBasicasFilasExD.h"
#include "EADFila.h"
#include "OperacoesBasicasPilhasExD.h"
#include "EADPilha.h"

#include "OperacoesFilasPilhasExD.h"

PNodoFila trocarPrimeiroUltimo(PNodoFila F);
PNodoFila organizarFila(PNodoFila F, int N);

int main()
{
  PNodoFila Queue;
  PNodoPilha Stack;
  Queue = criarFilaAleatoria(2, 15);

  printf("Fila atual: \n");
  mostrarFila(Queue);

  printf("Trocar primeiro com ultimo: \n");
  mostrarFila(trocarPrimeiroUltimo(Queue));

  printf("Organizar fila: \n");
  mostrarFila(organizarFila(Queue, 73000));

  printf("\n\nFila invertida: \n");
  mostrarFila(inverterFila(Queue));
}

PNodoFila inverterFila(PNodoFila F) {
  PNodoPilha P = criarPilha();

  while (F != NULL)
  {
    P = push(frente(F), P);
    F = remover(F);
  }

  while (P != NULL) 
  {
    F = juntar(topo(P), F);
    P = pop(P);
  }

  return F;
}

PNodoFila organizarFila(PNodoFila F, int N) {
  PNodoFila AuxGreater = criarFila();
  PNodoFila AuxLess = criarFila();
  
  while (F != NULL)
  {
    if(frente(F).numAluno >= N) AuxGreater = juntar(frente(F), AuxGreater);
    else AuxLess = juntar(F->Elemento, AuxLess);    
    
    F = remover(F);
  }

  while (AuxGreater != NULL) {
    F = juntar(frente(AuxGreater), F);
    AuxGreater = remover(AuxGreater);
  }

  while (AuxLess != NULL)
  {
    F = juntar(frente(AuxLess), F);
    AuxLess = remover(AuxLess);
  }
  
  return F;
}

PNodoFila trocarPrimeiroUltimo(PNodoFila F) {
  PNodoFila Aux = criarFila();  
  INFOFila head, last;

  head = frente(F);
  F = remover(F);

  while (F != NULL)
  {
    if(F->Seg == NULL) {
      last = frente(F);
      F = remover(F);
      break;
    }
 
    Aux = juntar(frente(F), Aux);
    F = remover(F);
  }
  
  F = juntar(last, F);
  Aux = juntar(head, Aux);

  while (Aux != NULL)
  {
    F = juntar(frente(Aux), F);
    Aux = remover(Aux);
  }

  return F;
}