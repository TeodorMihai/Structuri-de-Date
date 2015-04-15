#ifndef __stiva
#define __stiva


/*Functiile pentru stiva, va fi o lista simplu inlantuita, cu elemtul inital head. Inserarea se face la inceputul listei, schimband si adresa lui head. */
// data_type e o instructiune ce trebuie executata
void push_stiva(Nod** head, data_type x) { 

	Nod* nou = malloc(sizeof(Nod));

	nou->next = NULL;
	nou->inf = x;

	if(*head == NULL) /* Daca stiva e goala */

		*head = nou;
		else {

		nou->next = *head;
		*head = nou;

	}
}

data_type pop_stiva(Nod** head) {  /* Se prespunem ca nu aplicam aceasta operatie daca stiva e goala, (verificam inainte cu empty_stiva) */

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
		head = head->next;
}

int isEmpty_stiva(Nod* head) { // returneaza true daca e goala

	if(head == NULL)
		return 1;
	return 0;
}



#endif
