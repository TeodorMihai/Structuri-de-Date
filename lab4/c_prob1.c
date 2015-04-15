#include <stdio.h>
#include <stdlib.h>

typedef struct Nod {

	int inf;
	struct Nod *next; 
	struct Nod *prev;
} Nod;


void adauga(Nod **cap, int x) { /* se trimite ca dublu pointer ca in caz ca lista este vida sa poata fi initializata */
	
	Nod *curent;
	
	Nod *nou = malloc(sizeof(Nod));
	
	nou->inf = x;
	nou->next = NULL;
	nou->prev = NULL;

	if(*cap == NULL) 

		*cap = nou;
	else {

		curent = *cap;
		while(curent->next != NULL)
				curent = curent->next;
		curent->next = nou;
		nou->prev = curent;

	}
}

Nod* cauta(Nod *cap, int x) {

	while(cap != NULL) {

		printf("%d\n", cap->inf);
		if(cap->inf == x)
			return cap;
		cap = cap->next;
	}
	return NULL;
}



//Nod* sterge(Nod *cap, Nod *to_remove) {

int main() {

	Nod *p;
	
	adauga(&p, 6);
	adauga(&p, 12);
	adauga(&p, 13);
	printf("%p", p);

	//Nod *po = (Nod* )malloc(sizeof(Nod));

	//printf("%d\n", p->next->inf);
	//Nod *t = malloc(sizeof(Nod));
	//cauta(p, 12);
	//printf("%d", x->inf);
	return 0;
}