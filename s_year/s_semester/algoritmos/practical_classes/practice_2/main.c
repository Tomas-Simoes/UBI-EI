int maior(PNodoAB T, int A) {
	if(T == NULL) {
		return -1;
	}

	int highestL = maior(T->Esquerda, A);
	int highestR = maior(T->Direita, A);

	if(T->Elemento.ano == A) {
		int highest = (highestL > highestR) ? highestL : highestR;
		return (highest > T->Elemento.ano) ? highest : T->Elemento.ano;
	}

	return (highestL > highestR) ? highestL : highestR;
}

int main() {
	PNodoAB T = criarAB(0, 20);
	mostrarAB(T);

	int A = (T->Esquerda != NULL) ? T->Esquerda.ano : 2024;
	printf("A=%d", A);
	printf("highest=%d", maior(T, A));
}
