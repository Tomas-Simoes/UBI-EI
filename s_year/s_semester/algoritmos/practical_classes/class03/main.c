#include <stdio.h>
#include <stdlib.h>

#include "../../lib/Aleatorio.h"
#include "OperacoesBasicasExA.h"
#include "../../lib/EADLista.h"
#include "OperacoesExA.h"

int main()
{
    PNodoLista Lista; // struct NodoLista* lista

    Lista = criarListaAleatoria(0, 15);

    printf("Lista do inicio: \n");
    mostrarListaInicio(Lista);

    printf("Lista apartir do fim: \n");
    mostrarListaFimRec(Lista);

    printf("Tamanho da lista: %d\n", tamanhoLista(Lista));
    printf("Tamanho da lista recursivamente: %d\n", tamanhoListaRec(Lista));

    printf("Quantidade de notas finais igual a 5: %d\n", quantidadeNotaFinalRec(Lista, 5));
    printf("Quantidade de notas finais maior ou igual a 5: %d\n", quantidadeNotaFinalMaior(Lista, 5));

    printf("Maior nota: %d\n", maiorNotaFinal(Lista));
    printf("Maior nota recursivamente: %d\n", maiorNotaFinalRec(Lista, Lista->Elemento.notaFinal));

    printf("Melhor aluno: %d\n", melhorAluno(Lista));
    printf("Melhor aluno recursivamente: %d\n", melhorAlunoRec(Lista, NULL));
}