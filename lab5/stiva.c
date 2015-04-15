#ifndef __stiva
#define __stiva

#define data_type int

typedef struct nod {

	data_type inf;
	struct nod* next;
} nod;

nod* push_stiva(nod** head, data_type x) {

	nod* nou = malloc(sizeof(nod));

	nou->next = NULL;
	nou->inf = x;

	if(*head == NULL) {

		*head = nou;
		return nou;

	} else {

		nod *cur = *head;

		nou->next = cur;
		return nou;
	}

}

data_type pop_stiva(nod** head) { // gresit trebuie refacut

	nod* to_delete = *head;
	data_type to_return = (*head)->inf;

	(*head) = (*head)->next;
	free(to_delete);
	return to_return;
}

data_type peek_stiva(nod* head) {

	return head->inf;
}

void afis(nod* head) {

	while(head != NULL)
		printf("%d\n", head->inf),
		head = head->next;
}

int isEmpty(nod* head) {

	if(head == NULL)
		return 1;
	return 0;
}

int main() {

	nod* p = NULL;

	printf("Stiva e goala: %d\n", isEmpty(p));
	p = push_stiva(&p, 4);
	p = push_stiva(&p, 5);
	p = push_stiva(&p, 22);
	pop_stiva(&p);
	p = push_stiva(&p, 11);
	p = push_stiva(&p, 19);
	p = push_stiva(&p, 12);
	pop_stiva(&p);
	pop_stiva(&p);

	afis(p);
	printf("Ultimul element: %d\n", peek_stiva(p));

	return 0;

}

#endif