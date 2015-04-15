#include <stdio.h>
#include <stdlib.h>


typedef struct element {

	int x;
	struct element* next;
} elem, *link;
int main() {
	elem* t = malloc(sizeof(elem));
	link p;
	p = malloc(sizeof(elem));
	p-> x = 6;
	printf("%d",*p );
	return 0;

}