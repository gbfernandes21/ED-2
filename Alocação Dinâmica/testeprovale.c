#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE_CACHE 1

typedef struct Cache{
	int value;
	struct Cache* prev;
	struct Cache* next;
}Cache;

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

Cache* insert_node_head_list(Cache* head_list, int value){
	Cache* new = malloc(sizeof(Cache));
	
	new->value = value;
	new->prev = NULL;
	new->next = head_list;
	if(head_list) head_list->prev = new;
	
	return new;
}

Cache* update_head_list(Cache* head_list, int target){
	if(head_list->value == target) return head_list;
	
	Cache* new_head = head_list->next;
	
	while(new_head){
		if(new_head->value == target) break;
		new_head = new_head->next;
	}
	
	new_head->prev->next = new_head->next;
	
	if(new_head->next) new_head->next->prev = new_head->prev;
	
	new_head->prev = NULL;
	new_head->next = head_list;
	head_list->prev = new_head;
	
	return new_head;
}

Cache* pop(Cache* head_list){
	Cache* last = head_list;
	
	while(last->next)
		last = last->next;
	last->prev->next = NULL;
	free(last);
	
	return head_list;
}

int exist_value_in_list(Cache* head_list, int target){
	while(head_list){
		if(head_list->value == target) return 1;
		head_list = head_list->next;
	}
	return 0;
}

Cache* lru(Cache* head_list, int value, int size_cache, int* count){
	if(exist_value_in_list(head_list, value)) return update_head_list(head_list, value);
	
	if(*count < size_cache){
		(*count)++;
		return insert_node_head_list(head_list, value);
	}
	
	(size_cache == MIN_SIZE_CACHE) ? head_list = NULL : pop(head_list);
		
	return insert_node_head_list(head_list, value);
}

void print_cache(Cache* head_list){
	if(!head_list)
		printf("\n(Cache Vazio)\n");
	else{
		printf("\nCache: [ ");
		while(head_list){
			printf("%d ", head_list->value);
			head_list = head_list->next;
		}
		printf("]\n");
	}
}

void free_cache(Cache* head_list){
	while(head_list){
		Cache* next = head_list->next;
		free(head_list);
		head_list = next;
	}
}

int main(){
	Cache* cache = NULL;
	int value, count = 0, size = set_size_cache();
	printf("\nValores: ");
	
	do{
		scanf(" %d", &value);
		if(value <= 0) break;
		cache = lru(cache, value, size, &count);
	}while(1);
	
	print_cache(cache);
	free_cache(cache);
	
	return 0;
}
