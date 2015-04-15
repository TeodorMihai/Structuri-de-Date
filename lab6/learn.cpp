#include <iostream>
#include <stdio.h>

int main() {

	int x = 1; int y = 2;
	int& rx = x;
	rx = 4;
	printf("%d\n", rx);
	return 0;
}