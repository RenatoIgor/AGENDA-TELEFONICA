#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED
#define null NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct contato{

    char nome[81];/*Nome contato*/
    char tel[12];/*ddd+número de contato, ex. 21955557777*/
    struct contato *prox; /*ponteiro para a estrutura de lista encadeada*/
};
typedef struct contato Contato; //renomeacao da estrutura

// prototipos das funcoes
void inicia( Contato *LISTA);
int menu(void);
void opcao(Contato *LISTA, int op);
int contarContatos(Contato *LISTA);
void insereOrdenado(Contato *LISTA);
void exibe(Contato *LISTA);
void libera(Contato *LISTA);
void excluirContato(char nome[] ,Contato *LISTA);
void buscarContatoNome(char nome[],Contato *LISTA);
void gravar( Contato *LISTA);
void ler( Contato *LISTA);

void inicia( Contato *LISTA){
	LISTA->prox = null;

/*	Contato *p,*aux = ;
	while(!feof(arq)){
        p = (Contato *)malloc(sizeof(Contato));

        fscanf(arq,"%s\t%s",p->nome,p->tel);

	}
*/
}

int menu(void){
	int opt;

	printf("\nEscolha a opcao\n");
	printf("0. Sair\n");
	printf("1. Exibir contatos\n");
	printf("2. Adicionar Contato\n");
	printf("3. Limpar Agenda\n");
	printf("4. Excluir Contato\n");
	printf("5. Buscar contatos\n");
	printf("Opcao: "); scanf("%d", &opt);

	return opt;
}

void opcao(Contato *LISTA, int op){

	char nome[80];
	switch(op){
		case 0:
            gravar(LISTA);
			libera(LISTA);
			break;

		case 1:system("clear");
            printf("\n\n\t\tAGENDA TELEFONICA\n\n");
			exibe(LISTA);
			break;

		case 2:system("clear");
            printf("\nNovo Contato\n");
			insereOrdenado(LISTA);
			break;

		case 3:system("clear");
            printf("\nTodos os contatos removidos!\n");
		    libera(LISTA);
			inicia(LISTA);
			break;

        case 4:system("clear");
            printf("\nNome: ");
                scanf(" %s",nome);
            excluirContato(nome ,LISTA);
            break;

        case 5:
        	printf("\nNome: ");
        		scanf(" %s",nome);
        	buscarContatoNome(nome,LISTA);
        	break;
		default:
			printf("\nComando invalido\n\n");
	}
}

int vazia(Contato *LISTA){
	if(LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

void insereOrdenado(Contato *LISTA){

	Contato *novo=(Contato *) malloc(sizeof(Contato));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}

	printf("\nNome: "); scanf(" %[^\n]s",novo->nome);

	int i = 0;

	while(i < strlen(novo->nome)){// Formatar o nome ex: JoAo -> Joao, paula-> Paula
		novo->nome[i] = tolower(novo->nome[i]);
		if(i == 0 || novo->nome[i-1] == ' '){
			novo->nome[i] = toupper(novo->nome[i]);
		}
		i++;
	}

	printf("Numero: "); scanf("%11s",novo->tel);
	novo->prox = NULL;   // Novo contato criado

	if(vazia(LISTA)){ // se a lista esta vazia adciona contato direto
		LISTA->prox = novo;
    }


	else{
		Contato *tmp = LISTA->prox;
		Contato *ant = LISTA;

        if(contarContatos(LISTA) == 1){               // no caso de ter um contato,
			if(strcmp(tmp->nome,novo->nome) > 0){//verifica a ordem alfabetica
                                                 //e troca a posicao dos contatos
                novo->prox = tmp;
				ant->prox = novo;

				return;
			}
			tmp->prox = novo;
			return;
		}

		do{ // caso tenha mais de um contato insere o novo ja ordenado
			if(strcmp(tmp->nome,novo->nome) > 0){

				novo->prox = tmp;
				ant->prox = novo;

				return;
			}

			ant = ant->prox;
			tmp = tmp->prox;

		}while( tmp->prox != null  ||  novo->prox != null);


        if(strcmp(tmp->nome,novo->nome) > 0){
            ant->prox = novo;
            novo->prox = tmp;
            return;
        }
		tmp->prox = novo; //insere novo contato caso ele esteja na ultima posicao

	}
}

void excluirContato(char nome[],Contato *LISTA){
    Contato *tmp,*ant;
    int i = 0;

    while(i < strlen(nome)){// Formatar o nome ex: JoAo -> Joao, paula-> Paula
		nome[i] = tolower(nome[i]);
		if(i == 0 || nome[i-1] == ' '){
			nome[i] = toupper(nome[i]);
		}
		i++;
	}


    if(LISTA->prox == NULL){
        printf("\nNao existem contatos!\n");

    }
    else{
        tmp = LISTA->prox;ant = LISTA;
        while(tmp != null && strcmp(tmp->nome,nome) != 0){//fax a busca por nome na lista

            ant = tmp;
            tmp = tmp->prox;

        }

        if(tmp != NULL){
            ant->prox = tmp->prox;
            free(tmp);

            printf("\n%s excluido!\n\n",nome);
        }

        else{printf("\n%s nao encontrado!\n\n",nome);
        }

    }

}

int contarContatos(Contato *LISTA){

int cont = 0;
Contato *aux;
    if(vazia(LISTA)){
        return cont;
    }
    else{
        aux = LISTA->prox;
        while(aux != null){
            cont++;
            aux = aux->prox;
        }
    }

    return cont;
}

void exibe(Contato *LISTA){

	if(vazia(LISTA)){

		printf("Lista vazia!\n\n");
		return ;
	}

	Contato *tmp;
	tmp = LISTA->prox;
    printf("CONTATO(S)-> %d\n",contarContatos(LISTA));
    printf("------------------------------------------\n");
	while( tmp != NULL){
		printf("Nome: %s\n",tmp->nome);
		printf("Numero: %s\n\n",tmp->tel);

		tmp = tmp->prox;
	}

	printf("------------------------------------------\n\n");
}

void libera(Contato *LISTA){//exclui todos os elementos da lista
	if(!vazia(LISTA)){
		Contato *proxContato,
			  *atual;

		atual = LISTA->prox;
		while(atual != NULL){
			proxContato = atual->prox;
			free(atual);
			atual = proxContato;
		}
	}LISTA->prox = null;
}

void buscarContatoNome(char nome[],Contato *lista){

    int i = 0;

	while(i < strlen(nome)){// Formatar o nome ex: JoAo -> Joao, paula-> Paula
		nome[i] = tolower(nome[i]);
		if(i == 0 || nome[i-1] == ' '){
			nome[i] = toupper(nome[i]);
		}
		i++;
	}

    Contato *tmp;
   	char substring[80];
   	strcpy(substring,nome);
   	char *aux;

	//int j = 0;
	int vazia = 1;
	tmp = lista;
	printf("\n----------------------------------------\n");
	while(tmp){//fax a busca por nome na lista
      aux = strstr(tmp->nome,substring);

		if(aux != NULL){
			//lista[j] = tmp[i];
			printf("\nNOME:  %s\n",tmp->nome);
			printf("TELEFONE: %s\n", tmp->tel);
			vazia = 0;
		}
		tmp = tmp->prox;
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe ,%s nao encontrado!\n",nome );
	}

}

void gravar( Contato *LISTA){

    FILE* arq;

    arq = fopen("agenda.txt","w");

    if(arq == null){
        printf("\nErro na leitura!\n\n");
        exit(1);
    }

    Contato *tmp;
    tmp = LISTA->prox;

    Contato c;

    while(tmp != null){

        strcpy(c.nome,tmp->nome);
        strcpy(c.tel,tmp->tel);
        fprintf(arq,"%s %s\n",c.nome,c.tel);

        tmp = tmp-> prox;
    }

    fclose(arq);

}

void ler( Contato *LISTA){

    Contato *tmp,*novo;
    tmp = LISTA;

    Contato c;

    FILE *arq;

    arq = fopen("agenda.txt","r");
    if(arq == NULL){

        printf("ERRO!\n");
        exit(1);
    }

    while( fscanf(arq,"%s %s",&c.nome,&c.tel) != EOF){

        if(c.nome != null){
            novo = (Contato*)malloc(sizeof(Contato));
            strcpy(novo->nome,c.nome);
            strcpy(novo->tel,c.tel);
            novo->prox = null;

            if(vazia(LISTA)){ // se a lista esta vazia adciona contato direto
            LISTA->prox = novo;
            }

            else{

                while(tmp->prox != NULL){
                    tmp = tmp->prox;
                }
            tmp->prox = novo;
            }
        }

        //printf("%s %s\n",c.nome,c.tel);
    }
   // printf("%s %s\n",c.nome,c.tel);
    fclose(arq);
}

#endif // BIBLIOTECA_H_INCLUDED
