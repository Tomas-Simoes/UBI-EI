#include<stdio.h>
#include<stdlib.h>

#include "Aleatorio.h"
#include "OperacoesBasicasExA.h"
#include "EADLista.h"
#include "practice.h"

PNodoLista gerarListaAleatoria(int A, int B);
int func(PNodoLista L, int num);
int funcRec(PNodoLista L, int num);
int maiorNotaFinal(PNodoLista L);
int menorNotaFinalMaiorN(PNodoLista L, int num);
int quantidadeNotaFinalEntre(PNodoLista L, int A, int B);
int quantidadeNotaFinalEntreRec(PNodoLista L, int A, int B);
PNodoLista removerPrimeirosNElementos(PNodoLista L, int N);

int main(int argc, char *argv[]) {
	PNodoLista L = gerarListaAleatoria(2, 15); 
	mostrarListaInicio(L);

	int sum = func(L, L->Elemento.notaFinal);

	printf("\n soma das notas iguais a %d: %d\n", L->Elemento.notaFinal, sum);
	printf("mesma coisa mas recursiva: %d\n", funcRec(L, L->Elemento.notaFinal));
	printf("maior nota: %d\n", maiorNotaFinal(L));
	printf("menor nota maior que 10: %d\n", menorNotaFinalMaiorN(L, 10));
	printf("quantidade nota final entre 0 e 10: %d\n", quantidadeNotaFinalEntre(L, 0, 10));
	printf("mesma coisa mas rec: %d\n", quantidadeNotaFinalEntreRec(L, 0, 10));
	printf("lista sem os 3 primeiros elementos: \n");;

	PNodoLista L2 = removerPrimeirosNElementos(L, 3);
	mostrarListaInicio(L2);


}

PNodoLista gerarListaAleatoria(int A, int B) {
	int tam = gerarNumeroInteiro(A, B);
	PNodoLista L = criarLista();

	for(int i = 0; i < tam; i++) {
		L = inserirListaInicio(criarElementoLista(), L);
	}

	return L;
}

int func(PNodoLista L, int num) {
	int sum = 0;

	while(L != NULL) {
		if (L->Elemento.notaFinal == num) {
			sum += L->Elemento.notaFinal;
		}

		L = L->Prox;
	}

	return sum;
}

int funcRec(PNodoLista L, int num) {
	if (L == NULL) {
		return 0;
	}

	int sum = 0;

	if (L->Elemento.notaFinal == num) {
		sum = num + funcRec(L->Prox, num);
	} else {
		sum = 0 + funcRec(L->Prox, num);
	}

	return sum;
}

int maiorNotaFinal(PNodoLista L) {
	int maior = L->Elemento.notaFinal;
	L = L->Prox;

	while (L != NULL){
		if (L->Elemento.notaFinal > maior) {
			maior = L->Elemento.notaFinal;
		}
		L = L->Prox;
	}

	return maior;
}

int menorNotaFinalMaiorN(PNodoLista L, int num) {
	int menor;

	if (L->Elemento.notaFinal >= num) {
		menor = L->Elemento.notaFinal;
	}

	while (L != NULL) {
		if(L->Elemento.notaFinal >= num && L->Elemento.notaFinal < menor) {
			menor = L->Elemento.notaFinal;
		}

		L = L->Prox;
	}

	return menor;
}

int quantidadeNotaFinalEntre(PNodoLista L, int A, int B){
	int num = 0;

	while(L != NULL) {
		if(L->Elemento.notaFinal >= A && L->Elemento.notaFinal <= B){
			num++;
		}
		L = L->Prox;
	}

	return num;
}

int quantidadeNotaFinalEntreRec(PNodoLista L, int A, int B) {
	if(L == NULL) {
		return 0;
	}

	int num = 0;

	if(L->Elemento.notaFinal >= A && L->Elemento.notaFinal <= B) {
		num = 1 + quantidadeNotaFinalEntreRec(L->Prox, A, B);
	} else {
		num = 0 + quantidadeNotaFinalEntreRec(L->Prox, A, B);
	}

	return num;
}

PNodoLista removerPrimeirosNElementos(PNodoLista L, int N) {
	int i = 0;
	PNodoLista L2 = L;

	while(L2 != NULL && i < N)
	{	L2 = removerLista(L2->Elemento, L2);
		i++;
	}

	return L2;
}
