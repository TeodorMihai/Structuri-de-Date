#ifndef __coada
#define __coada


#define data_type int

typedef struct  Nod{

	data_type inf;
	struct Nod* next;
} Nod;

void push_coada(Nod** head, Nod** end, data_type x) { //inserera la final

	Nod* nou = malloc(sizeof(Nod));
	nou->next = NULL;
	nou->inf = x;

	if(*head == NULL) 

		*head = *end = nou;
	else {
		(*end)->next = nou;
		*end = nou;
	}
}

data_type pop_coada(Nod** head) { //sterge de la inceput

	Nod* to_delete = *head;
	data_type to_return = to_delete->inf;

	(*head) = (*head)->next;

	free(to_delete);

	return to_return;
}

data_type peek_coada(Nod* head) { //returneza urmatoare instructiune

	return head->inf;
}

int isEmpty_coada(Nod* end) {

	if(end == NULL)
		return 1;
	return 0;
}



void afis_coada(Nod* head) {


	while(head != NULL) {

		printf("%d ", head->inf);
		head = head->next;
	}
	printf("\n");
}

#endif