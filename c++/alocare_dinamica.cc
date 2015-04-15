#include <stdio.h>

const int N = 10;
const int M = 10;

//int **mat; merge declarat si aici

int main(int argc, char const *argv[]) {
	/* code */
	int **mat = NULL;

	mat = new int*[N];

	for(int i = 0 ;i < N; ++i)
		mat[i] = new int[M];
	
	mat[4][5] = 5;

	printf("%d\n", mat[4][5]);
	//dezalocare

	for(int i = 0 ;i < N; ++i)
			delete[] mat[i];
	delete[] mat;	
		
	//sau daca se stiu dimensiunile la compile time putem aloca
	//int (*mat)[100] = new int [N][100];
	//delete [] mat;
	return 0;
}