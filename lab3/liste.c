#include <stdio.h>
#include <stdlib.h>


typedef struct Nod {
	int val;
	struct Nod* next;
} Nod;


void init(Nod **p, int x) {
	
	(*p) = malloc(sizeof(Nod));
	(*p)->val = x;
	(*p)->next = NULL;
}

void afis(Nod *p) {
	
	while(p -> next != NULL) {
		printf("%d\n", p->val);
		p = p -> next;
	}
	printf("%d\n", p->val);
}	

void addF(Nod *p, int x) {
	
	Nod* nou = malloc(sizeof(Nod));
	
}

int main() {
	
	Nod* p;
	
	init(&p, 7);	
	addF(p, 5);	
	afis(p);
	return 0;
}

