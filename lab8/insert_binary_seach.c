#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Nod_arb{


	int inf;
	struct Nod_arb* st;
	struct Nod_arb* dr;

} Nod_arb;


void insert(Nod_arb** p, int x) {

	if(*p == NULL) {

		*p = malloc(sizeof(Nod_arb));
		(*p)->inf = x;
		(*p)->st = NULL;
		(*p)->dr = NULL;
		return ;
	} 

	Nod_arb* cur = *p;
	
	if(cur->inf < x) {
		if(cur->dr != NULL)
			insert(&cur->dr, x);
		else {

			Nod_arb* nou = malloc(sizeof(Nod_arb));
			nou->st = nou->dr = NULL;
			nou->inf = x;
			cur->dr = nou;
		}	
	} else {

		if(cur->st != NULL)
			insert(&cur->st, x);
		else {

			Nod_arb* nou = malloc(sizeof(Nod_arb));
			nou->st = nou->dr = NULL;
			nou->inf = x;
			cur->st = nou;
		}

	}
}

void DFS(Nod_arb* cur) {

	if(cur == NULL)
		return ;
	printf("%d\n", cur->inf);
	DFS(cur->st);
	DFS(cur->dr);
}

void BFS(Nod_arb* root) {

	Nod_arb *v[100];

	int head = 0; int tail = 0;

	v[head] = root;
	while(head <= tail) {

		Nod_arb* cur = v[head];

		if(cur->st != NULL)
			v[++tail] = cur->st;
		if(cur->dr != NULL)
			v[++tail] = cur->dr;

		printf("%d\n", cur->inf); 
		head++;
	}
}

int get_height(Nod_arb* p) { 

	if(p == NULL)
		return 0;
	int height_left = get_height(p->st);
	int height_right = get_height(p->dr);

	return max(height_left, height_right) + 1;
}

int max(int a, int b) { return a > b ? a : b;}

int det(Nod_arb *p) {

	if(p == NULL) 
		return 0;
	
	int max_left; int max_right; int Max;

	max_right = get_height(p->dr);
	max_left = get_height(p->st);

	Max = max_left + max_right + 1;
	return max(Max, max(max_left, max_right));

}

int number_leafs(Nod_arb* root) {

	if(root->st == NULL)
		return 1;
	if(root->dr == NULL)
		return 1;

	int leafs_right = number_leafs(root->dr);
	int leafs_left = number_leafs(root->st);

	return leafs_right + leafs_left;

}	

int stiva[100]; 

int get_way(Nod_arb* cur) {


	stiva[++stiva[0]] = cur->inf;
	if(cur->st == NULL && cur->dr == NULL) {

		for(int i = 1; i <= stiva[0]; ++i)
				printf("%d ", stiva[i]);
		printf("\n");
	}
	if(cur->st != NULL) {
		get_way(cur->st); 	
		stiva[0]--;
	}
	if(cur->dr != NULL) {
		get_way(cur->dr);
		stiva[0]--;
	}

}

int main() {

	Nod_arb* root = NULL;
	srand(time(NULL));
	insert(&root, 4);
	insert(&root, 2);
	for(int i = 0 ;i < 22; ++i)
		insert(&root, rand() );
	DFS(root);
	BFS(root);
	printf("%d\n", det(root));
	printf("%d\n", number_leafs(root));
	get_way(root);
	return 0;
}