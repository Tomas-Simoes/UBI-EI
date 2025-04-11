PNodoLista criarListaAleatoria(int A, int B);

int pesquisarAlunoNota(PNodoLista L, int nota);
void bigFunc();

PNodoLista criarListaAleatoria(int A, int B)
{
    PNodoLista L;
    int N, i;

    N = gerarNumeroInteiro(A, B);
    L = criarLista();
    i = 0;
    while (i < N)
    {
        INFOLista element = criarElementoLista();

        if (pesquisarLista(element, L) == 0)
        {
            L = inserirListaInicio(element, L);
            i++;
        }
    }

    return L;
}

int pesquisarAlunoNota(PNodoLista L, int nota) {
    int menorNumAluno = -1;

    while (L != NULL)
    {
        if (L->Elemento.notaFinal == nota){
            if (L->Elemento.numAluno < menorNumAluno || menorNumAluno == -1) {
                menorNumAluno = L->Elemento.numAluno;
            }
        }

        L = L->Prox;
    }

    return menorNumAluno;
}

void func() {
    PNodoLista L =  criarListaAleatoria(1, 15);
    mostrarListaInicio(L);

    PNodoLista segundoL = L->Prox;

    if (segundoL != NULL) {
        INFOLista segundoEl = segundoL->Elemento;

        printf("Notas MTP e TE do segundo aluno: ");
        printf("%.2f, %.2f (MTP)  %.2f, %.2f (TE)", segundoEl.notasMTP[0], segundoEl.notasMTP[1],
                                            segundoEl.notasTE[0], segundoEl.notasTE[1]);
    }

    printf("\nNota final do primeiro elemento: %d", L->Elemento.notaFinal);
    printf("\nMenor valor de numAluno com nota 10: %d\n", pesquisarAlunoNota(L, 10));
}
