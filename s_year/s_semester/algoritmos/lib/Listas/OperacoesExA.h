PNodoLista criarListaAleatoria(int A, int B);

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

