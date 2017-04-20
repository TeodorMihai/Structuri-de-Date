#include <stdio.h>
#include <stdlib.h>


typedef struct PQ {

	int N;
	int v[10000];

}PQ;

void swap(int *a, int *b){

	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void percolate(PQ *pq, int index) {

	
	if(index <= 1) return ;

	if(pq->v[index/2] > pq->v[index]) {
		//printf("asdasd");	

		swap(&(pq->v[index/2]), &(pq->v[index]));
		percolate(pq, index/2);
	}
}

void initPQ(PQ *pq) {

	pq->N = 0;
}

void addPQ(PQ *pq, int value) {

	pq->N++;
	pq->v[pq->N] = value;
	percolate(pq, pq->N);
}

void printPQ(PQ pq) {

	for(int i = 1;i <= pq.N; ++i)
		printf("%d ", pq.v[i]);
	printf("\n");
}


void sift(PQ *pq, int index) {

	int ind = 0;

	if(pq->N >= index * 2)
		ind = index * 2;
	if(pq->N >= index * 2 + 1 && pq->v[index * 2 + 1] < pq->v[ind])
		ind = index * 2 + 1;

	if(ind != 0 && pq->v[index] < pq->v[ind]) {

		swap(&(pq->v[index]), &(pq->v[ind]));
		sift(pq, ind);
	}


}

int delPQ(PQ *pq) {

	pq->v[1] = pq->v[pq->N];
	pq->N--;
	sift(pq, pq->N);

}

int emptyPQ(PQ pq) {

	if(pq.N == 0)
		return 1;
	return 0;
}


int main() {


	PQ pq;
	int x[10] = {3,8,2,9,7,1,5,4,6,0};

	initPQ(&pq);
	for(int i = 0; i < 10; ++i) {

		addPQ(&pq, x[i]);

		printPQ(pq);
	}

	while(!emptyPQ(pq)) {

		printf("%d\n", delPQ(&pq));
	}


	return 0;
}