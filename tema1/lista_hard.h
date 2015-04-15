#ifndef __lista_hard
#define __lista_hard


/* Retin hard-ul ca o simpla, avand in plus parametrii up, down care pentru toate casutele in afara celor cu index-ul 0 vor avea 
valoarea NULL. Pentru cele cu index-ul 0 vor pointa catre primul element din linia de mai sus(cel cu indexul 0),
 respectiv linia de mai jos*
 Initial am crezut ca nu pot retine adresa pe un pointer de 32 de biti,
 asa ca am retinut-o pe un unsigned short int(de 16 iti folosind operatii pe biti) */

int convert(char c) { //practic asociez lui 0 -> 0 , 1 -> 1...A -> 10, B -> 11...F -> 15

	if(isdigit(c))
		return c - '0';
	else  return c - 'A' + 10;
}

char reconvert(int x) { /* Inversa functiei de mai sus */

	if(x < 10)
		return x + '0';
	else return x + 'A' - 10;
}

void _NodHard(NodHard* nod, int _ind, int _line, int _damage, char* _adr) { /* Un fel de constructor ca sa stez mai repede valorile unui nod */

	nod->ind = _ind;
	nod->line = _line;
	nod->damage = _damage;

	nod->adr = convert(_adr[0]) + (convert(_adr[1]) << 4) + (convert(_adr[2]) << 8) + (convert(_adr[3]) << 12); 
	/* Un element dintr-o adresa e retinut pe 4 biti, in short int-ul nod->adr retin toata adresa, 4 blocuri de 4 biti */
}

char* get_address(unsigned short int x) {

	/* Adresa e retinuta cum am explicat mai sus, acum pentru a obtine fiecare element selectez blocuri de 4 biti, si convertesc la caracter,
	lipind toate elementele obtin adresa mea de 4 caractere */

	char* s = malloc(sizeof(char) * 5);	

	int mask = (1 << 4) - 1;

	s[0] = reconvert(x & mask);
	s[1] = reconvert(x >> 4 & mask);
	s[2] = reconvert(x >> 8 & mask);
	s[3] = reconvert(x >> 12 & mask);
	s[4] = '\0';
	
	return s;
}

void move_toward(NodHard** nod, int ind, int line) {
 /* Ma mu spre elementul cu indicele ind, de pe linia line */

	if((*nod)->ind == 0) {
		
		if((*nod)->line < line) {

			(*nod) = (*nod)->up;
			return ;
		}
		
		if((*nod)->line > line) {
			(*nod) = (*nod)->down;
			return ;
		}

		if((*nod)->line == line && (*nod)->ind != ind) {
			(*nod) = (*nod)->next;
			return ;
		}
	} else {

		if((*nod)->line != line || (*nod)->ind != ind)

				(*nod) = (*nod)->next;
	}


}


void printNodHard(NodHard* nod, FILE* out) { /* Pentru ebugging */

	fprintf(out, "indice: %d, linie: %d, damage: %d, adresa: %s\n", nod->ind, nod->line, nod->damage, get_address(nod->adr) );
}


void __NodHard(NodHard *nod) { /* Un fel de constructor */

	nod->up = NULL;
	nod->down = NULL;
	nod->next = NULL;
}

NodHard* create_list(int max_lines) { 

	 NodHard* first_Nod_old_line = NULL; /* ca sa fac legatura intre linia pe care o creez acum si cea anterioara */
	NodHard* to_return = NULL;/* pentru a retine adresa elementului de pe linia 0 si coloana 0, il returnez la final */


	int cnt = 4;

	for(int i = 0 ; i < max_lines; ++i) { 

		int number_elements = (1 << cnt);

		NodHard* first = malloc(sizeof(NodHard)); //aloca nodul cu indicele 0 pentru fiecare linie
		__NodHard(first);

		if(i == 0) { //daca suntem in plus si pe prima linie 

			_NodHard(first, 0, 0, 0, "0000");

			first->down = NULL; // nu are linie mai jos de ea
			first_Nod_old_line = first; 
			to_return = first;//vom returna nodul de pe linia 0 si indexul 0
	
		} else { 

			first->down = first_Nod_old_line; //nodul de pe linia i, indexul 0 are o legatura cu casuta de pe linia i - 1 si indexul 0
			first->up = NULL; //momentan nu stim catre ce va avea legatura, punem NULL
			_NodHard(first, 0, i, 0, "0000");  //inseram valorile
			first_Nod_old_line->up = first; //si nodul anterior de pe linia i - 1, index 0 are legatura cu acesta, e bidirectionala
			first_Nod_old_line = first; 

		}

		NodHard* old_Nod = first; // il retin pentru ca nodul cu indexul cel mai mare va trebui sa aiba o legatura cu acesta
		//Acum cream restul membrilor, toti cei care au indexul diferit de 0

		for(int j = 1; j < number_elements; ++j) {

			NodHard* cur = malloc(sizeof(NodHard));
			__NodHard(cur);

			if(j == number_elements - 1) { // daca sunt in nodul cu indexul ce mai mare(ultimul de pe linie)

				_NodHard(cur, j, i, 0 , "0000");
			
				cur->next = first; // facem legatura de la ultimul nod de pe o linie la primul
				cur->up = NULL;
				cur->down = NULL;
				old_Nod->next = cur; //nodul anterior are o legatura cu nodul actual

				continue;
			}

			_NodHard(cur, j, i, 0 , "0000");
			cur->next = NULL;
			cur->up = NULL; //nu poti face trecerea intre linii de pe nodurile care nu au indexul 0
			cur->down = NULL;

			old_Nod->next = cur; //facem o legatura intre nodul anterior si nodul curent
			old_Nod = cur; //ne mutam in urmatorul nod
		}

		++cnt; //ne mutam pe urmatoare linie care are mai multe casute

	}
	return to_return;
}

void print_hard_disk(NodHard* first, int max_lines, FILE *out) {

	int cnt = 4;
	for(int i = 0 ;i < max_lines; ++i) {

		int number_elements = (1 << cnt);
		for(int j = 0 ; j < number_elements ; ++j) 
			first = first->next;
		
		first = first->up;
		cnt++;
	}

}



#endif