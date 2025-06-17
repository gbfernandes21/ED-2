/*GABRIEL FERNANDES DOS SANTOS
 * QUINTA-FEIRA, 26/06/2025
 * BSI, TURMA 124*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

typedef struct No{
	int dado;
	struct No* prox;
}No;

No* preencher_lista(No* lst); //Preenche a lista com números aleatórios até receber um valor == 0.
int interface();
void wait();
void printLine(int n);
void printar_lista(No* lst); //Mostra todos os valores da lista.
void acessar_memoria(No* lst);
void mostrar_cache(No* lst, int tam); //Mostra os valores presentes no Cache com base no tamanho informado pelo usuário.

void wait(){
	setbuf(stdin, NULL);
	getchar();
}

void printLine(int n){
	for (int i = 0; i < n; i++)
		printf("-");
	printf("\n");
}

No* preencher_lista(No* lst){
	No* new = malloc(sizeof(No));
	
	new->dado = rand()%MAX;
	new->prox = lst;
	
	if(new->dado)
		return preencher_lista(new); 
	return new; 
}

void printar_lista(No* lst){
	if(!lst) return;
	
	printar_lista(lst->prox);
	printf("[%d] ", lst->dado); //Printa os valores "Empilhados" pela recursão.
}

void mostrar_cache(No* lst, int tam){
	int cont = 0;
	int v[MAX] = {0}; //Controla os valores que já foram printados.
	
	while(cont < tam && lst){
		int i = lst->dado;
		
		if(!v[i] && i){ //Se determinado valor ainda não foi printado, sendo esse valor != 0...
			printf("[%d] ", i);
			v[i] = 1;
			cont++;
		}
		
		lst = lst->prox;
	}
}

int interface(){
	system("clear");
	printLine(40);
	printf("\n1 - ACESSAR MEMÓRIA\n\n0 - SAIR\n\n");
	printLine(40);
	
	int op;
	printf("Opção: ");
	scanf(" %d", &op);
	
	return op;
}

void acessar_memoria(No* lst){
	system("clear");
	printf("Tamanho do cache: ");
	int tam;
	scanf(" %d", &tam);
	
	printf("\nValores: ");
	printar_lista(lst);
	printf("\n\nCache: ");
	mostrar_cache(lst, tam);
	wait();
}

int main(){
	srand(time(NULL));
	No* lst = NULL;
	lst = preencher_lista(lst);
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1: acessar_memoria(lst);
			break;
			default: printf("Opção Inválida!\n");
			wait();
			break;
		}
	}while(1);
}
