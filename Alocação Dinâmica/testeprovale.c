#include <stdio.h>
#include <stdlib.h>

typedef struct Cache{
	int num;
	struct Cache* ant;
	struct Cache* prox;
}Cache;

int exist(Cache* head, int alvo);//Verifica se o valor já existe dentro do Cache.
int set_size_cache(); //Retorna o tamanho do Cache informado pelo Usuário.
void free_list(Cache* head);
void print_cache(Cache* head);
Cache* pop(Cache* head); //Deleta o último elemento da lista.
Cache* insert_node(Cache* head, int num); //Adiciona elemento no topo da lista.
Cache* update_position(Cache* head, int num); //Atualiza o topo da lista.
Cache* lru(Cache* head, int num, int size, int* cont); //Lógica central do algoritmo LRU.

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

int exist(Cache* head, int alvo){
	if(!head) return 0;
	
	while(head){
		if(head->num == alvo) return 1;
		head = head->prox;
	}
	return 0;
}

Cache* insert_node(Cache* head, int num){
	Cache* new = malloc(sizeof(Cache));
	
	new->num = num;
	new->ant = NULL;
	new->prox = head;
	if(head) head->ant = new;
	
	return new;
}

Cache* update_position(Cache* head, int num){
	Cache* atual = head;
	
	while(atual){
		if(atual->num == num) break;
		atual = atual->prox;
	}
	
	if(atual == head) return head;
	
	if(atual->ant) atual->ant->prox = atual->prox;
	
	if(atual->prox) atual->prox->ant = atual->ant;
	
	atual->prox = head;
	atual->ant = NULL;
	head->ant = atual;
		
	return atual;
}

Cache* pop(Cache* head){
	Cache* last = head;
	
	while(last->prox)
		last = last->prox;
	if(last->ant) last->ant->prox = NULL;
	free(last);
	return head;
}

Cache* lru(Cache* head, int num, int size, int* cont){
	if(exist(head, num)) return update_position(head, num);
	
	if(*cont < size){
		(*cont)++;
		return insert_node(head, num);
	}
	
	head = pop(head);
	
	return insert_node(head, num);
}

void print_cache(Cache* head){
	if(!head){
		printf("\n(Cache Vazio)\n");
		return;
	}
	
	printf("\nCache: [ ");
	while(head){
		printf("%d ", head->num);
		head = head->prox;
	}
	printf("]\n");
}

void free_list(Cache* head){
	while(head){
		Cache* next = head->prox;
		free(head);
		head = next;
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
