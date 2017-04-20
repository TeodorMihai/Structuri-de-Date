#ifndef __coada
#define __coada

typedef struct  {

	Nod_arb* inf;
	struct Nod* next;

}Nod;

void push_coada(Nod** head, Nod** end, Nod_arb* x) { //inserera la final

	Nod* nou = malloc(sizeof(Nod));
	nou->next = NULL;
	nou->inf = malloc(sizeof(Nod_arb));
	nou->inf = x;

	if(*head == NULL) 

		*head = *end = nou;
	else {
		(*end)->next = nou;
		*end = nou;
	}
}

Nod pop_coada(Nod** head) { //sterge de la inceput

	Nod* to_delete = *head;
	Nod to_return = to_delete->inf;

	(*head) = (*head)->next;

	free(to_delete);

	return to_return;
}

Nod_arb* peek_coada(Nod* head) { //returneza urmatoare instructiune

	return head->inf;
}

int isEmpty_coada(Nod* end) {

	if(end == NULL)
		return 1;
	return 0;
}



void afis_coada(Nod* head) {


	while(head != NULL) {

		printf("%d\n", head->inf->inf);
		head = head->next;
	}
}

#endif