#include <stdio.h>
#include <stdlib.h>

#define data_type int

typedef struct nod {

	data_type inf;
	struct nod* next;
} nod;

void push_coada(nod** head, nod** end, data_type x) {

	nod* nou = malloc(sizeof(nod));
	nou->next = NULL;
	nou->inf = x;

	if(*head == NULL) 

		*head = *end = nou;
	else {

		(*end)->next = nou;
		*end = nou;
	}
}

data_type pop_coada(nod** head) { // trebuei trimis dubla pointer pentru eliberarea memoriei?

	nod* to_delete = *head;
	data_type to_return = to_delete->inf;

	(*head) = (*head)->next;

	free(to_delete);

	return to_return;
}

data_type peek_coada(nod* head) {

	return head->inf;
}

int isEmpty_coada(nod* head) {

	if(head == NULL)
		return 1;
	return 0;
}



void afis_coada(nod* head) {

	while(head != NULL) {
		printf("%d\n", head->inf);
		head = head->next;
	}
}


int main(int argc, char const *argv[]) {
		

	nod* head = NULL;
	nod* end = NULL;

	push_coada(&head, &end, 3);
	push_coada(&head, &end, 8);
	push_coada(&head, &end, 12);

	//printf("%d\n", end->inf);
	printf("%d\n", pop_coada(&head));

	//afis_coada(head);

	return 0;
}