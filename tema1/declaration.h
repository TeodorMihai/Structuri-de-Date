#ifndef __declaration
#define __declaration


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>


const int READ_DATA = 5;
const int WRITE = 30;
const int READ_DAMAGE = 2;

typedef struct Instruction { //o instructiune data din input

	char* type; // w, r, mw, mr sau d
	int line; 
	int ind; //inidice
	char *code; //in caz ca avem comanda w sau mw sau stimc e trebuie sa scriem
	int tmp; // timpul pana cand vom citi urmatoarea comada, acum imi dau seama cred ca e degeaba
	int nr; // nr de comenzi (mai mult de uan la bonus)

} Instruction;


#define data_type Instruction // pentru stiva si coada

typedef struct Nod { //pentru stiva si coada

	data_type inf;
	struct Nod* next;
} Nod;


typedef struct NodHard { // pentru hard

	
	int ind;
	int line;
	
	int damage;
	
	unsigned short int adr;

	struct NodHard* next; //nodul cu indicele cu 1 mai mare decat cel acutal
	struct NodHard* up; //up si down o sa fie NULL in toate nodurile care nu au indicele 0
	struct NodHard* down;

} NodHard;

#endif
