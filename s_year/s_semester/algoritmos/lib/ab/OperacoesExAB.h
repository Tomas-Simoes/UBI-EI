/* ------------------------------------------------------- */
/* ---- prot�tipos/headers das fun��es da biblioteca ----- */
/* ------------------------------------------------------- */

PNodoAB gerarABAleatoria(int A, int B);

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

