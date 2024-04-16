
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


// ler e devolver um inteiro maior ou igual a inf
int lerNumeroInteiroMaiorIgualInf (int inf){
  int aux, num;
  
  do{
  	printf("Insira um inteiro maior ou igual a %d: ", inf);
  	scanf("%d", &num);
  }while(num < inf);
  
  return num;
  
}
