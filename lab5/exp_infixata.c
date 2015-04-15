#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stiva.h"


int prioritate(char c) {

	if(c == '(' || c == ')')
		return 0;
	if(c == '+' || c == '-')
		return 2;
	if(c == '*' || c == '/')
		return 1;
	return 3;
}

int main() {

	char *s = malloc(100);

	nod *rez = NULL;
	nod *oper = NULL;
	scanf("%s", s);

	for(int i = 0 ;i < strlen(s); ++i) {
		if(isdigit(s[i]))
			rez = push_stiva(&rez, s[i]);
		if(prioritate(s[i]) != 3)
			while(!isEmpty(oper)  && prioritate(peek_stiva(oper)) >= prioritate(s[i]))
				rez = push_stiva(&rez, pop_stiva(&oper));
		oper = push_stiva(&oper, s[i]);
	}
	afis(oper);

	return 0;
}