#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int *x = malloc(sizeof(int));
	*x = 5;

	int t =8;
	x = &t;
	printf("%d\n", *x);
	return 0;
}
