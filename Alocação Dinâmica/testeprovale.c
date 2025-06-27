#include <stdio.h>
#include <stdlib.h>

typedef struct Cache{
	int num;
	struct Cache* ant;
	struct Cache* prox;
}Cache;

int exist(Cache* lst, int alvo);//Verifica se o valor já existe dentro do Cache.
int set_size_cache(); //Retorna o tamanho do Cache informado pelo Usuário.
void free_list(Cache* lst);
void print_cache(Cache* lst);
Cache* pop(Cache* lst); //Deleta o último elemento da lista.
Cache* insert_node(Cache* lst, int num); //Adiciona elemento no topo da lista.
Cache* update_position(Cache* lst, int num); //Atualiza o topo da lista.
Cache* lru(Cache* lst, int num, int size, int* cont); //Lógica central do algoritmo LRU.

int set_size_cache(){
	int size;
	
	do{
		system("clear");
		printf("Tamanho do Cache: ");
		scanf(" %d", &size);
		if(size <= 0) continue;
		return size;
	}while(1);
}

int exist(Cache* lst, int alvo){
	if(!lst) return 0;
	
	while(lst){
		if(lst->num == alvo) return 1;
		lst = lst->prox;
	}
	return 0;
}

Cache* insert_node(Cache* lst, int num){
	Cache* new = malloc(sizeof(Cache));
	
	new->num = num;
	new->ant = NULL;
	new->prox = lst;
	if(lst) lst->ant = new;
	
	return new;
}

Cache* update_position(Cache* lst, int num){
	Cache* atual = lst;
	
	while(atual){
		if(atual->num == num) break;
		atual = atual->prox;
	}
	
	if(atual == lst) return lst;
	
	if(atual->ant) atual->ant->prox = atual->prox;
	
	if(atual->prox) atual->prox->ant = atual->ant;
	
	atual->prox = lst;
	atual->ant = NULL;
	lst->ant = atual;
		
	return atual;
}

Cache* pop(Cache* lst){
	Cache* last = lst;
	
	while(last->prox)
		last = last->prox;
	if(last->ant) last->ant->prox = NULL;
	free(last);
	return lst;
}

Cache* lru(Cache* lst, int num, int size, int* cont){
	if(exist(lst, num)) return update_position(lst, num);
	
	if(*cont < size){
		(*cont)++;
		return insert_node(lst, num);
	}
	
	lst = pop(lst);
	
	return insert_node(lst, num);
}

void print_cache(Cache* lst){
	if(!lst){
		printf("\n(Cache Vazio)\n");
		return;
	}
	
	printf("\nCache: [ ");
	while(lst){
		printf("%d ", lst->num);
		lst = lst->prox;
	}
	printf("]\n");
}

void free_list(Cache* lst){
	while(lst){
		Cache* next = lst->prox;
		free(lst);
		lst = next;
	}
}

int main(){
	Cache* cache = NULL;
	int num, cont = 0, tam = set_size_cache();
	printf("\nValores: ");
	
	do{
		scanf(" %d", &num);
		
		if(num <= 0) break;

		cache = lru(cache, num, tam, &cont);
	}while(1);
	
	print_cache(cache);
	free_list(cache);
	
	return 0;
}
