#include <stdio.h>
#include <stdlib.h>

int maxi(int x, int y) {
	
	return x > y ? x : y;
}

int find_max(int v[], int st, int dr) {
	
	if(st == dr) return v[st];
	int mid = (st + dr) / 2;

	return maxi(find_max(v, st, mid), find_max(v, mid + 1, dr));
	
}

int main() {
	
	int N; int v[100];

	scanf("%d", &N);
	for(int i = 0 ;i < N; ++i)
		scanf("%d", &v[i]);
	
	printf("%d\n", find_max(v, 0, N - 1));

	return 0;
}
