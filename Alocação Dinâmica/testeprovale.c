#include <stdio.h>
#include <stdlib.h>

typedef struct Cache{
	int num;
	struct Cache* ant;
	struct Cache* prox;
}Cache;

int exist(Cache* top, int alvo);//Verifica se o valor já existe dentro do Cache.
int set_size_cache(); //Retorna o tamanho do Cache informado pelo Usuário.
void free_list(Cache* top);
void print_cache(Cache* top);
Cache* pop(Cache* top); //Deleta o último elemento da lista.
Cache* insert_node(Cache* top, int num); //Adiciona elemento no topo da lista.
Cache* update_position(Cache* top, int num); //Atualiza o topo da lista.
Cache* lru(Cache* top, int num, int size, int* cont); //Lógica central do algoritmo LRU.

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

int exist(Cache* top, int alvo){
	if(!top) return 0;
	
	while(top){
		if(top->num == alvo) return 1;
		top = top->prox;
	}
	return 0;
}

Cache* insert_node(Cache* top, int num){
	Cache* new = malloc(sizeof(Cache));
	
	new->num = num;
	new->ant = NULL;
	new->prox = top;
	if(top) top->ant = new;
	
	return new;
}

Cache* update_position(Cache* top, int num){
	Cache* atual = top;
	
	while(atual){
		if(atual->num == num) break;
		atual = atual->prox;
	}
	
	if(atual == top) return top;
	
	if(atual->ant) atual->ant->prox = atual->prox;
	
	if(atual->prox) atual->prox->ant = atual->ant;
	
	atual->prox = top;
	atual->ant = NULL;
	top->ant = atual;
		
	return atual;
}

Cache* pop(Cache* top){
	Cache* last = top;
	
	while(last->prox)
		last = last->prox;
	if(last->ant) last->ant->prox = NULL;
	free(last);
	return top;
}

Cache* lru(Cache* top, int num, int size, int* cont){
	if(exist(top, num)) return update_position(top, num);
	
	if(*cont < size){
		(*cont)++;
		return insert_node(top, num);
	}
	
	top = pop(top);
	
	return insert_node(top, num);
}

void print_cache(Cache* top){
	if(!top){
		printf("\n(Cache Vazio)\n");
		return;
	}
	
	printf("\nCache: [ ");
	while(top){
		printf("%d ", top->num);
		top = top->prox;
	}
	printf("]\n");
}

void free_list(Cache* top){
	while(top){
		Cache* next = top->prox;
		free(top);
		top = next;
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
