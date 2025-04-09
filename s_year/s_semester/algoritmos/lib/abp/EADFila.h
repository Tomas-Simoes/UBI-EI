// tipos de dados

struct NodoFila
{
    INFOFila Elemento;
    struct NodoFila *Seg;
};

typedef struct NodoFila *PNodoFila;

/* ------------------------------------------------------- */
/* ---- protótipos/headers das funções da biblioteca ----- */
/* ------------------------------------------------------- */

// Operações sobre um nodo (NodoFila)

PNodoFila criarNodoFila(INFOFila);

PNodoFila libertarNodoFila(PNodoFila);

// Operações sobre uma EAD Fila (PNodoFila)

PNodoFila criarFila();

int filaVazia(PNodoFila);

PNodoFila juntar(INFOFila, PNodoFila);

PNodoFila remover(PNodoFila);

INFOFila frente(PNodoFila);

/* ------------------------------------------------------- */
/* -------------- implementação das funções -------------- */
/* ------------------------------------------------------- */

// Operações sobre um nodo (NodoFila)

PNodoFila criarNodoFila(INFOFila X)
{
    PNodoFila P;
    P = (PNodoFila)malloc(sizeof(struct NodoFila));
    if (P == NULL)
        return NULL;
    P->Elemento = X;
    P->Seg = NULL;
    return P;
}

PNodoFila libertarNodoFila(PNodoFila P)
{
    P->Seg = NULL;
    free(P);
    P = NULL;
    return P;
}

// Operações sobre uma EAD Fila (PNodoFila)

PNodoFila criarFila()
{
    PNodoFila Q;
    Q = NULL;
    return Q;
}

int filaVazia(PNodoFila Q)
{
    if (Q == NULL)
        return 1;
    else
        return 0;
}

PNodoFila juntar(INFOFila X, PNodoFila Q)
{
    PNodoFila P, Novo;
    Novo = criarNodoFila(X);
    if (Novo == NULL)
        return Q;
    if (filaVazia(Q))
    {
        Q = Novo;
        return Q;
    }
    P = Q;
    while (P->Seg != NULL)
        P = P->Seg;
    P->Seg = Novo;
    return Q;
}

PNodoFila remover(PNodoFila Q)
{
    PNodoFila P;
    P = Q;
    Q = Q->Seg;
    P = libertarNodoFila(P);
    return Q;
}

INFOFila frente(PNodoFila Q)
{
    return Q->Elemento;
}
