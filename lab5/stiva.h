#ifndef __stiva
#define __stiva

#define data_type int

typedef struct Nod {

	data_type inf;
	struct Nod* next;
} Nod;

void push_stiva(Nod** head, data_type x) {

	Nod* nou = malloc(sizeof(Nod));

	nou->next = NULL;
	nou->inf = x;

	if(*head == NULL) 

		*head = nou;
		else {

		nou->next = *head;
		*head = nou;

	}

}

data_type pop_stiva(Nod** head) { // gresit trebuie refacut

	Nod* to_delete = *head;
	data_type to_return = (*head)->inf;

	(*head) = (*head)->next;
	free(to_delete);
	return to_return;
}

data_type peek_stiva(Nod* head) {

	return head->inf;
}

void afis(Nod* head) {

	while(head != NULL)
		printf("%d\n", head->inf),
		head = head->next;
}

int isEmpty(Nod* head) {

	if(head == NULL)
		return 1;
	return 0;
}


#endif