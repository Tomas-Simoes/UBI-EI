
/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

PNodoLista criarListaAleatoria(int A, int B);
int tamanhoLista(PNodoLista L);
int tamanhoListaRec(PNodoLista L);
int quantidadeNotaFinalRec(PNodoLista L, int N);
int quantidadeNotaFinalMaior(PNodoLista L, int N);
int maiorNotaFinal(PNodoLista L);
int maiorNotaFinalRec(PNodoLista L, int highest);
int melhorAluno(PNodoLista L);
INFOLista melhorAlunoRec(PNodoLista L);
INFOLista piorAlunoRec(PNodoLista L);
double mediaFinal(PNodoLista L);
INFOLista piorAlunoMenorK(PNodoLista L, int k);
PNodoLista removerNota(PNodoLista, int nota);

/* ------------------------------------------------------- */
/* -------------- implementa��o das fun��es -------------- */
/* ------------------------------------------------------- */

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

int tamanhoLista(PNodoLista L)
{
    PNodoLista P;
    int tam;

    tam = 0;
    while (L != NULL)
    {
        tam++;
        L = L->Prox;
    }

    return tam;
}

int tamanhoListaRec(PNodoLista L)
{
    if (L == NULL)
    {
        return 0;
    }

    if (L->Prox == NULL)
    {
        return 1;
    }

    return 1 + tamanhoListaRec(L->Prox);
}

int quantidadeNotaFinalRec(PNodoLista L, int N)
{
    if (L == NULL)
    {
        return 0;
    }

    if (L->Elemento.notaFinal == N)
    {
        return 1 + quantidadeNotaFinalRec(L->Prox, N);
    }
    else
    {
        return 0 + quantidadeNotaFinalRec(L->Prox, N);
    }
}

int quantidadeNotaFinalMaior(PNodoLista L, int N)
{
    int num;

    num = 0;
    while (L != NULL)
    {
        if (L->Elemento.notaFinal >= N)
            num++;

        L = L->Prox;
    }

    return num;
}

int maiorNotaFinal(PNodoLista L)
{
    int highest;

    highest = L->Elemento.notaFinal;
    L = L->Prox;
    while (L != NULL)
    {
        if (L->Elemento.notaFinal > highest)
        {
            highest = L->Elemento.notaFinal;
        }

        L = L->Prox;
    }

    return highest;
}

int maiorNotaFinalRec(PNodoLista L, int highest)
{
    if (L == NULL)
    {
        return highest;
    }

    if (L->Elemento.notaFinal > highest)
    {
        return maiorNotaFinalRec(L->Prox, L->Elemento.notaFinal);
    }
    else
    {
        return maiorNotaFinalRec(L->Prox, highest);
    }
}

int melhorAluno(PNodoLista L)
{
    PNodoLista bestStudent = L;
    L = L->Prox;

    int highestTE = bestStudent->Elemento.notasTE[0] + bestStudent->Elemento.notasTE[1];

    while (L != NULL)
    {
        int sum = L->Elemento.notasTE[0] + L->Elemento.notasTE[1];

        if (sum > highestTE)
        {
            highestTE = sum;
            bestStudent = L;
        }

        L = L->Prox;
    }

    return bestStudent->Elemento.numAluno;
}

INFOLista melhorAlunoRec(PNodoLista L)
{
    INFOLista best;

    if (L->Prox == NULL)
    {
        return L->Elemento;
    }

    best = melhorAlunoRec(L->Prox);

    int sumL = L->Elemento.notasTE[0] + L->Elemento.notasTE[1];
    int sumBest = best.notasTE[0] + best.notasTE[1];

    if (sumL > sumBest)
    {
        return L->Elemento;
    }
    else
    {
        return best;
    }
}

INFOLista piorAlunoRec(PNodoLista L)
{
    INFOLista worst;

    if (L->Prox == NULL)
    {
        return L->Elemento;
    }

    worst = piorAlunoRec(L->Prox);

    int sumL = L->Elemento.notasMTP[0] + L->Elemento.notasMTP[1];
    int sumWorst = worst.notasMTP[0] + worst.notasMTP[1];

    if (sumL < sumWorst)
    {
        return L->Elemento;
    }
    else
    {
        return worst;
    }
}

double mediaFinal(PNodoLista L)
{
    if (L == NULL)
    {
        return 0;
    }

    int sum = 0;
    int size = 0;

    while (L != NULL)
    {
        sum += L->Elemento.notaFinal;
        size++;

        L = L->Prox;
    }

    return sum / size;
}

INFOLista piorAlunoMenorK(PNodoLista L, int k)
{
    INFOLista worst;

    if (L->Prox == NULL)
    {
        return L->Elemento;
    }

    worst = piorAlunoMenorK(L->Prox, k);

    int sumL = L->Elemento.notasMTP[0] + L->Elemento.notasMTP[1];
    int sumWorst = worst.notasMTP[0] + worst.notasMTP[1];

    if (sumL < k && sumL < sumWorst)
    {
        return L->Elemento;
    }
    else if (sumWorst < k)
    {
        return worst;
    }
    else
    {
        return criarElementoLista();
    }
}

PNodoLista removerNota(PNodoLista L, int nota)
{
    while (L != NULL && L->Elemento.notaFinal == nota)
    {
        PNodoLista P = L;
        L = L->Prox;

        libertarLista(P);
    }

    PNodoLista ant = L;
    L = L->Prox;

    return L;
}
