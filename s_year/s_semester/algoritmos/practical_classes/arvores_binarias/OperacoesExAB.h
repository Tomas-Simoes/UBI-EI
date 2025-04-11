/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

PNodoAB gerarABAleatoria(int A, int B);

// Ex. 3
int quantidadeDeElementos(PNodoAB T);

// Ex. 5
int sumNotaFinal(PNodoAB T);
float mediaNotaFinal(PNodoAB T);

// Ex. 6
int maiorNotaFinal(PNodoAB T);
int maiorNotaFinal2(PNodoAB T);

// Ex. 11
int quantidadeNos1Filho(PNodoAB T);

// Ex. 12
int nivelDoElemento(INFOAB X);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

PNodoAB gerarABAleatoria(int A, int B)
{
    PNodoAB T;
    int T_size;

    T = criarAB();
    T_size = gerarNumeroInteiro(A, B);

    for (int i = 0; i < T_size; i++)
    {
        INFOAB el = criarElementoAB();
        while (pesquisarAB(el, T) == NULL)
        {
            T = inserirPorAlturaAB(el, T);
        }
    }

    return T;
}

int quantidadeDeElementos(PNodoAB T)
{
    int amount = 0;

    if (ABVazia(T) == 1)
    {
        return 0;
    }

    return 1 + quantidadeDeElementos(T->Esquerda) + quantidadeDeElementos(T->Direita);
}

int sumNotaFinal(PNodoAB T)
{
    if (T == NULL)
    {
        return 0;
    }

    return T->Elemento.notaFinal + sumNotaFinal(T->Esquerda) + sumNotaFinal(T->Direita);
}

float mediaNotaFinal(PNodoAB T)
{
    int sum = sumNotaFinal(T);
    int size = quantidadeDeElementos(T);

    return (float)sum / size;
}

int maiorNotaFinal(PNodoAB T)
{
    if (T == NULL)
    {
        return -1;
    }

    int higherEsq = maiorNotaFinal(T->Esquerda);
    int higherDir = maiorNotaFinal(T->Direita);

    if (higherEsq > higherDir)
        return (T->Elemento.notaFinal > higherEsq) ? T->Elemento.notaFinal : higherEsq;
    else
        return (T->Elemento.notaFinal > higherDir) ? T->Elemento.notaFinal : higherDir;
}

int maiorNotaFinal2(PNodoAB T)
{
    int highest, highestEsq, highestDir;

    if (T->Esquerda == NULL && T->Direita == NULL)
        return T->Elemento.notaFinal;

    highest = T->Elemento.notaFinal;

    if (T->Esquerda != NULL)
    {
        highestEsq = maiorNotaFinal2(T->Esquerda);

        if (highestEsq > highest)
            highest = highestEsq;
    }

    if (T->Direita != NULL)
    {
        highestDir = maiorNotaFinal2(T->Direita);

        if (highestDir > highest)
            highest = highestDir;
    }

    return highest;
}

int quantidadeNos1Filho(PNodoAB T)
{
    // arvore vazia ou sem filhos
    if (T == NULL || (T->Esquerda == NULL && T->Direita == NULL))
        return 0;

    // arvore com os dois filhos
    if (T->Esquerda != NULL && T->Direita != NULL)
        return 0 + quantidadeNos1Filho(T->Esquerda) + quantidadeNos1Filho(T->Direita);

    // arvore só com filho na esquerda
    if (T->Esquerda != NULL && T->Direita == NULL)
        return 1 + quantidadeNos1Filho(T->Esquerda);

    // arvore só com filho na direita
    if (T->Esquerda == NULL && T->Direita != NULL)
        return 1 + quantidadeNos1Filho(T->Direita);
}

int nivelDoElemento(PNodoAB T, INFOAB X)
{
    if (pesquisarAB(X, T) == 0)
    {
        return -1;
    }
}
