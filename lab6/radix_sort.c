#include <stdio.h>
#include <stdlib.h>
	
#include "coada.h"

int get_pow(int nr) {

	int x = 1;

	for(int i = 0 ;i < nr; ++i)
			x = x * 10;
	return x;
}

int get_digit(int x, int nr) {

	return (x / get_pow(nr - 1)) % 10;
}

int main() {

	Nod* head[10]; Nod* head_aux[10];
	Nod* end[10]; Nod* end_aux[10];

	FILE* in = fopen("radix.in", "r");
	FILE* out = fopen("radix.out", "w");


	for(int i = 0; i < 10; ++i)	
		head[i] = NULL, end[i] = NULL, head_aux[i] = NULL, end_aux[i] = NULL;

	int N; int v[100];

	fscanf(in, "%d", &N);

	for(int i = 0; i < N; ++i)
		fscanf(in, "%d", &v[i]);

	for(int i = 0 ;i < N; ++i) 
			push_coada(&head[v[i] % 10], &end[v[i] % 10], v[i]);


	for(int k = 2 ;k <= 12; ++k) {

		for(int i = 0 ;i < 10; ++i) {

			while(!isEmpty_coada(head[i])) {

				int a = pop_coada(&head[i]);
				
				push_coada(&head_aux[get_digit(a, k)], &end_aux[get_digit(a, k)], a);
			}
		}

		for(int i = 0; i < 10; ++i) {

			while(!isEmpty_coada(head_aux[i]))

				push_coada(&head[i], &end[i], pop_coada(&head_aux[i]) );
			
		}
	}

	for(int i = 0 ;i < 10; ++i)
		while(!isEmpty_coada(head[i]))
				fprintf(out, "%d\n", pop_coada(&head[i]));

	return 0;
}