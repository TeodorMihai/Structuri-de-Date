#include <stdio.h>
#include <stdlib.h>

int check[100]; 

int main() {
	
	char *s = malloc(100); int p[100];

	scanf("%s", s);

	int k = 1;
	while(k > 0) {
		
		for(int i = 0 ;i < strlen(s); ++i) {
			if(check[i] == 0) {
				check[i] = 1;
				p[k] = i;
				if( k == strlen(s) ) {
					for(int j = 1; j <= strlen(s); ++i)
						printf("%c", s[p[j]])
				}
				else {++k; i = 0;}			
			}
								
		}
		check[p[k]] = 0;
		--k;	
	}

	
	
	return 0;
}
