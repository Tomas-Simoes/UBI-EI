
// ler e devolver um inteiro entre inf e sup
int lerNumeroInteiroValido (int inf, int sup){
  int aux, num;
  
  if (inf > sup){ // troca-los
  	aux = inf;
  	inf = sup;
  	sup = aux;
  }
  // inf <= sup
  do{
  	printf("Insira um inteiro entre %d e %d: ", inf, sup);
  	scanf("%d", &num);
  }while(num < inf || num > sup);
  
  return num;
  
}

