#include <stdio.h>
#include <stdlib.h>

#include "stiva.h"

void push(Nod** head1, Nod** head2, data_type x) {

	push_stiva(head1, x);
}

data_type pop(Nod** head1, Nod** head2) {

	if(isEmpty_stiva(*head2)) {

		while(!isEmpty_stiva(*head1))
			push_stiva(head2, pop_stiva(head1));
		return pop_stiva(head2);

	} else return pop_stiva(head2);
	
}

int main() {

	Nod* head1 = NULL;
	Nod* head2 = NULL;

	push(&head1, &head2, 23);
	push(&head1, &head2, 1231);

	push(&head1, &head2, 12312);

	printf("%d\n", pop(&head1, &head2));
	printf("%d\n", pop(&head1, &head2));

	return 0;
}