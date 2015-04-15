#ifndef __lista
#define __lista


typedef struct Nod {

	char* command;
	struct Nod* next;
} Nod;


void insert_last(Nod** first, char* com) { //nu returneaza nimic pentru ca primul elemnt nu are cum sa schimbe in urma acestei oepratii

	Nod* curent;

	Nod* nou = malloc(sizeof(Nod));
	nou->command = malloc( (strlen(com) + 1) * sizeof(char) );
	strcpy(nou->command, com);
	nou->next = NULL;

	if(*first == NULL)
		*first = nou;
	else {

		curent = *first;
		while(curent->next != NULL)
			curent = curent->next;

		curent->next = nou;	
	}
}


Nod* insert_first(Nod** first, char* com) { //returneaza noul prim element al listei

	Nod* nou = malloc(sizeof(Nod));
	nou->command = malloc((strlen(com) + 1) * sizeof(char));
	strcpy(nou->command, com);

	if(*first == NULL) {
		
		*first = nou;
		return *first;
	
	} else {

		nou->next = *first;
		return nou;
	}
}


Nod* delete_last(Nod* first) { //daca lista are un singur element atunci trebuie sa returneze NULL(lista devine goala)

	if(first == NULL) return NULL;

	if(first->next == NULL) {

		free(first);
		return NULL;
	}

	Nod* first_aux = first;

	while(first->next->next != NULL)
		first = first->next;

	Nod* to_delete = first->next;
	first->next = NULL;
	free(to_delete);

	return first_aux;
}


Nod* delete_first(Nod* first) { //returneaza primul element

	if(first == NULL) return NULL;

	if(first->next == NULL) {

		free(first);
		return NULL;
	}

	Nod* to_delete = first;
	first = first->next;
	free(to_delete);

	return first;
}

Nod* get_last(Nod* first) {

	if(first == NULL) return NULL;

	while(first->next != NULL)
		first = first->next;

	return first;
}


void print(Nod* first) {

	while(first != NULL) {
		printf("%s\n", first->command);
		first = first->next;
	}
}

/*  Pentru teste: 
	Nod* lista = NULL;
	insert_last(&lista, "@#%23");
	insert_last(&lista, "blabla");

	lista = insert_first(&lista, "TERTe");
	lista = insert_first(&lista, "Sstr");
	insert_last(&lista, "cicaia");
	print(lista);

	printf("\n");
	lista = delete_first(lista);
	lista = delete_last(lista);
	lista = insert_first(&lista, "nanana");
	print(lista);
*/	
#endif