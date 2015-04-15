#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palindrom(char *s, int st, int dr) {
	
	if(st > dr) return 1;
	if(s[st] == s[dr]) return palindrom(s, st + 1, dr - 1);
	
	return 0;
}

int main() {

	char *s = malloc(100);
	scanf("%s", s);
	
	if(palindrom(s, 0, strlen(s) - 1))
		printf("Este palindrom\n");
	else printf("Nu este palindrom\n");
	
	return 0;
}
