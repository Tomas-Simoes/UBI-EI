#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <io.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct
{
	int             idAtm;
	int             idCliente;
	float           valor;
}   registo;

int  main(int argc, char *argv[])
{
	registo v;
	
	/* Modificar*/
    const int ATM=3;
    const int CLI=5;
	const int NumeroTransacts = 10;  //200
    const char * fnome = "data.bin";

	int  fddados = creat( fnome, S_IRUSR | S_IWUSR);
    if (fddados<0) {perror(NULL);return 1;}
    printf("Data File %s created ok\n",fnome);

	/*for (int j = 0; j < CLI; j++)
		for (int i = 0; i < ATM; i++)
		{
			v.idAtm = i;
			v.idCliente = j;
			v.valor = rand() % 10 - 5;
			write(fddados, &v, sizeof(v));
		}
		*/
	
	for (int i = 0; i < NumeroTransacts ; i++)
	{
		v.idAtm = rand() % ATM;
		v.idCliente = rand() % CLI;
		v.valor = rand() % 10 - 5.0;
		printf("Data: %3d  idAtm %3d  idCliente  %3d   Valor %f\n",i,v.idAtm,v.idCliente,v.valor);
		write(fddados, &v, sizeof(v));
	}

    return 0;
}
