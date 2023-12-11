#include <stdio.h>

int main()
{

  int vAnual;
  float imposto = 0;
  int escalao;
  char contribuinte;
  float taxa = 0.0;

  printf("Vencimento anual: ");
  scanf("%d", &vAnual);
  printf("Tipo de contibuinte (R: Reformado T: Trabalhador Ativo): ");
  scanf(" %c", &contribuinte);

  if (vAnual <= 20000)
  {
    escalao = 1;

    if (contribuinte == 'R')
      taxa = 0.08;
    else
      taxa = 0.14;
  }
  else
  {
    escalao = 2;

    if (contribuinte == 'R')
      taxa = 0.12;
    else
      taxa = 0.22;
  }

  imposto = imposto * taxa;

  printf("\n\nEscalao = %d \n Imposto = %f", escalao, imposto);
}