#include <stdio.h>
#include <stdlib.h>

#include "coada.h"

const int run_max = 5;

int min(int a, int b) {

	return a > b ? b : a;
}

int max(int a, int b) {

	return a > b ? a : b;
}

int main() {

	Nod* head = NULL; 
	Nod* end = NULL;

	int total_runtime = 0;

	
	int N;int v[100];

	scanf("%d", &N);
	
	for(int i = 0; i < N;  ++i) {
		scanf("%d", &v[i]);
		push_coada(&head, &end, v[i]);

	}

	while(!isEmpty_coada(head)) {

		int a = pop_coada(&head);
		total_runtime = total_runtime + min(5, a);

		if(a - 5 > 0)
			push_coada(&head,&end, a - 5);
		afis_coada(head);

	}

	
	return 0;
}