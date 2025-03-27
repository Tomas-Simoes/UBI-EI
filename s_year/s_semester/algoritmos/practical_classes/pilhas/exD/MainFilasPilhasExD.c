
#include <stdio.h>
#include <stdlib.h>

#include "Aleatorio.h"
#include "OperacoesBasicasFilasExD.h"
#include "EADFila.h"
#include "OperacoesBasicasPilhasExD.h"
#include "EADPilha.h"

#include "OperacoesFilasPilhasExD.h"

int main()
{
  PNodoFila Fila;
  Fila = criarFilaAleatoria(2, 15);

  mostrarFila(Fila);
}
