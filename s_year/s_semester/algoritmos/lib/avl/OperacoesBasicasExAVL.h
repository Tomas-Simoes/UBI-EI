
// tipo de dados

typedef int INFOAVL;


/* ------------------------------------------------------- */
/* ---- protótipos/headers das funções da biblioteca ----- */
/* ------------------------------------------------------- */

void mostrarElementoAVL (INFOAVL);

INFOAVL criarElementoAVL ();

// comparação de 2 elementos do tipo INFOAVL:
//   devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
int compararElementosAVL (INFOAVL, INFOAVL);


/* ------------------------------------------------------- */
/* -------------- implementação das funções -------------- */
/* ------------------------------------------------------- */


void mostrarElementoAVL (INFOAVL X)
{
  printf("%d\n", X);
}

INFOAVL criarElementoAVL ()
{
  INFOAVL X;
  do{
    printf("Insira um inteiro entre 10 e 99: ");  // por exemplo
    scanf("%d", &X);
  }while(X < 10 || X > 99);
  return X;
}

// comparação de 2 elementos do tipo INFOAVL:
//   devolve -1 se X < Y, 0 se X = Y, 1 se X > Y
int compararElementosAVL (INFOAVL X, INFOAVL Y)
{
  if (X > Y)
    return 1;
  if (X < Y)
    return -1;
  return 0;
}


