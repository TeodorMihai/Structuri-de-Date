#include <stdio.h>
#include <stdlib.h>


typedef struct Nod {

	int inf;
	struct Nod *next; 
	struct Nod *prev;
} Nod;

void adauga(Nod** cap, int x) {

	Nod* curent;
	Nod* nou = malloc(sizeof(Nod));

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

		if(cap->inf == x)
			return cap;
		cap = cap->next;
	}
	return NULL;
}

void sterge(Nod* cap, Nod* to_remove) {

	if(cap == NULL)
		return ;

	if(cap->next == NULL && to_remove == cap) {

		free(cap);
		return;
	}

	while(cap->next != NULL) {

		if(cap->next == to_remove) {

			if(cap->next->next != NULL) {

				Nod *skip = cap->next->next;
				cap->next = skip;
				skip->prev = cap;

				free(to_remove);

			} else {

				cap->next = NULL;
				free(to_remove);
			}
			return;
		}

		cap = cap->next;
	}

	if(cap == to_remove) {
		
		cap->next = NULL;
		free(to_remove);
	}
}


void afis(Nod* cap) {

	while(cap != NULL) {

		printf("%d\n", cap->inf);
		cap=cap->next;
	}
}

void insert_sum(Nod* cap) { //inseraaza suma celor 2 pointer vecini, creand un pointer nou

	while(cap->next != NULL) {

		Nod* nou = malloc(sizeof(Nod));
		Nod* skip = cap->next;

		nou->prev = cap;
		nou->next = skip;
		nou->inf = cap->inf + skip->inf;

		cap->next = nou;
		skip->prev = nou;

		cap = skip;
	}
}

void insert_sort(Nod *cap, int x) {

	if(cap->inf > x) {

		Nod *nou = malloc(sizeof(Nod));
		nou->next = cap;
		nou->prev = NULL;

		cap->prev = nou;
	}

	while(cap->next != NULL) {

		if(x < cap->next->inf) {

			Nod* skip = cap->next;

			Nod* nou = malloc(sizeof(Nod));

			nou->next = skip;
			nou->inf = x;
			nou->prev = cap;

			cap->next = nou;
			skip->prev = nou;
			return;
		}
		cap = cap->next;
	}

	if(cap->inf < x)
		adauga(&cap, x);

}

int main() {

	Nod *p = NULL;

	adauga(&p, 1);
	adauga(&p, 6);
	adauga(&p, 13);
	adauga(&p, 19);
	adauga(&p, 33);
	sterge(p, cauta(p, 13));
	sterge(p, cauta(p, 19));
	afis(p);
	//insert_sum(p);
	afis(p);

	insert_sort(p, 7);
	afis(p);
	return 0;
}