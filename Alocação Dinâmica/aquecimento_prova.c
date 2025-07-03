#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	int valor;
	struct Item* ant;
	struct Item* prox;
}Item;

typedef struct{
	Item* inicio;
	int cont;
}Lista;

int interface(){
	int op;
	printf("1 - Criar Item\n2 - Mostrar Itens\n3 - Excluir Item\n");
	scanf(" %d", &op);
	return op;
}

Lista* new_lista(){
	Lista* l = malloc(sizeof(Lista));
	l->inicio = NULL;
	l->cont = 0;
	return l;
}

void set_inicio(Lista* l, int num){
	Item* new = malloc(sizeof(Item));
	new->valor = num;
	
	if(!l->inicio){
		new->prox = new;
		new->ant = new;
		l->inicio = new;
	}else{
		Item* ultimo = l->inicio->ant;
		
		ultimo->prox = new;
		new->ant = ultimo;
		new->prox = l->inicio;
		l->inicio->ant = new;
		l->inicio = new;
	}
	l->cont++;
}

void set_final(Lista* l, int num){
	Item* new = malloc(sizeof(Item)), *ultimo = l->inicio->ant;
	new->valor = num;
	
	new->ant = ultimo;
	ultimo->prox = new;
	l->inicio->ant = new;
	new->prox = l->inicio;
	l->cont++;
}

void set(Lista* l){
	int num;
	
	printf("Digite um número: ");
	scanf(" %d", &num);
	
	if(!l->inicio || l->inicio->valor > num){
		set_inicio(l, num);
		return;
	}
	
	Item* i = l->inicio->prox;
	
	while(i != l->inicio){
		if(i->valor > num) break;
		i = i->prox;
	}
	
	if(i == l->inicio){
		set_final(l, num);
		return;
	}
	
	Item* new = malloc(sizeof(Item));
	new->valor = num;
	
	i->ant->prox = new;
	new->ant = i->ant;
	i->ant = new;
	new->prox = i;
	
	l->cont++;
}

void delete(Lista* l){
	if(!l->inicio) return;
	
	int num, achou = 0;
	Item* i = l->inicio;
	
	printf("Digite o valor que deseja excluir: ");
	scanf(" %d", &num);
	
	if(l->cont == 1 && l->inicio->valor == num){
		l->inicio = NULL;
		l->cont = 0;
		printf("Excluído!\n");
		return;
	}
	
	do{
		if(i->valor == num){
			achou = 1;
			break;
		}
		i = i->prox;
	}while(i != l->inicio);
	
	if(achou){
		i->ant->prox = i->prox;
		i->prox->ant = i->ant;
		
		if(i == l->inicio)
			l->inicio = i->prox;
		free(i);
		l->cont--;
		printf("Excluído!\n");
	}else
		printf("Valor não encontrado!\n");
}

void get_lista(Lista* l){
	if(!l->inicio) return;
	Item* i = l->inicio;
	printf("\n\n");
	do{
		printf("%d ", i->valor);
		i = i->prox;
	}while(i != l->inicio);
	printf("\n\n");
}

int main(){
	Lista* lista = new_lista();
	
	do{
		switch(interface()){
			case 0: return 0;
			case 1: set(lista);
			break;
			case 2: get_lista(lista);
			break;
			case 3: delete(lista);
			break;
			default:
			break;
		}
	}while(1);
}
