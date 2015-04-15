#include <stdio.h>
#include <stdlib.h>


typedef struct nod {
	
	int inf;
	struct nod *next;
} nod;

void insert(int val, nod *last) {
	
	
}

void init(int val, nod *first, nod *last) {
	
	first -> next = last -> next = NULL;
	first -> inf = last -> inf = val;
}

int main() {
	
	nod *first = NULL;
	nod *last = NULL;

	int N; int x;int ok = 0;

	scanf("%d", &N);

	while(N--) {
		scanf("%d", &x);
		if( ok == 0) initi(x, last, first);
		insert(x, last);
	}
	
	return 0;
}
