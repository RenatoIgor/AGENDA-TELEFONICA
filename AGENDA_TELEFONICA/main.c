#include "biblioteca.h"

int main()
{

	printf("\t\tAGENDA TELEFONICA\n\n");

    Contato *LISTA = (Contato *) malloc(sizeof(Contato));
	if(!LISTA){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	inicia(LISTA);
	ler(LISTA);

	int opt;

	do{
		opt = menu();
		opcao(LISTA,opt);
	}while(opt);

    free(LISTA);

	return 0;
}
